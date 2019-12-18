#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct queue {char* sender; char* id; int /*<<< orphan*/  mailf; int /*<<< orphan*/  queue; } ;
struct qitem {scalar_t__* sender; char* addr; int /*<<< orphan*/  mailf; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  bounceq ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPAND_WILDCARD ; 
 int /*<<< orphan*/  EX_IOERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int FULLBOUNCE ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_CRIT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char* VERSION ; 
 scalar_t__ add_recp (struct queue*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct queue*,int) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  delqueue (struct qitem*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,scalar_t__*,char*,char*,char*,char*,char*,char*,char const*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 char* hostname () ; 
 scalar_t__ linkspool (struct queue*) ; 
 scalar_t__ newspoolf (struct queue*) ; 
 char* rfc822date () ; 
 int /*<<< orphan*/  run_queue (struct queue*) ; 
 int /*<<< orphan*/  setlogident (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

void
bounce(struct qitem *it, const char *reason)
{
	struct queue bounceq;
	char line[1000];
	size_t pos;
	int error;

	/* Don't bounce bounced mails */
	if (it->sender[0] == 0) {
		syslog(LOG_INFO, "can not bounce a bounce message, discarding");
		exit(EX_SOFTWARE);
	}

	bzero(&bounceq, sizeof(bounceq));
	LIST_INIT(&bounceq.queue);
	bounceq.sender = "";
	if (add_recp(&bounceq, it->sender, EXPAND_WILDCARD) != 0)
		goto fail;

	if (newspoolf(&bounceq) != 0)
		goto fail;

	syslog(LOG_ERR, "delivery failed, bouncing as %s", bounceq.id);
	setlogident("%s", bounceq.id);

	error = fprintf(bounceq.mailf,
		"Received: from MAILER-DAEMON\n"
		"\tid %s\n"
		"\tby %s (%s);\n"
		"\t%s\n"
		"X-Original-To: <%s>\n"
		"From: MAILER-DAEMON <>\n"
		"To: %s\n"
		"Subject: Mail delivery failed\n"
		"Message-Id: <%s@%s>\n"
		"Date: %s\n"
		"\n"
		"This is the %s at %s.\n"
		"\n"
		"There was an error delivering your mail to <%s>.\n"
		"\n"
		"%s\n"
		"\n"
		"%s\n"
		"\n",
		bounceq.id,
		hostname(), VERSION,
		rfc822date(),
		it->addr,
		it->sender,
		bounceq.id, hostname(),
		rfc822date(),
		VERSION, hostname(),
		it->addr,
		reason,
		config.features & FULLBOUNCE ?
		    "Original message follows." :
		    "Message headers follow.");
	if (error < 0)
		goto fail;

	if (fseek(it->mailf, 0, SEEK_SET) != 0)
		goto fail;
	if (config.features & FULLBOUNCE) {
		while ((pos = fread(line, 1, sizeof(line), it->mailf)) > 0) {
			if (fwrite(line, 1, pos, bounceq.mailf) != pos)
				goto fail;
		}
	} else {
		while (!feof(it->mailf)) {
			if (fgets(line, sizeof(line), it->mailf) == NULL)
				break;
			if (line[0] == '\n')
				break;
			if (fwrite(line, strlen(line), 1, bounceq.mailf) != 1)
				goto fail;
		}
	}

	if (linkspool(&bounceq) != 0)
		goto fail;
	/* bounce is safe */

	delqueue(it);

	run_queue(&bounceq);
	/* NOTREACHED */

fail:
	syslog(LOG_CRIT, "error creating bounce: %m");
	delqueue(it);
	exit(EX_IOERR);
}