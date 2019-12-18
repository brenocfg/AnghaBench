#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct queue {int /*<<< orphan*/  queue; } ;
struct qitem {char* sender; char* queueid; char* queuefn; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  itmqueue ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct qitem* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct qitem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ add_recp (struct queue*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct queue*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  next ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static struct qitem *
readqueuef(struct queue *queue, char *queuefn)
{
	char line[1000];
	struct queue itmqueue;
	FILE *queuef = NULL;
	char *s;
	char *queueid = NULL, *sender = NULL, *addr = NULL;
	struct qitem *it = NULL;

	bzero(&itmqueue, sizeof(itmqueue));
	LIST_INIT(&itmqueue.queue);

	queuef = fopen(queuefn, "r");
	if (queuef == NULL)
		goto out;

	while (!feof(queuef)) {
		if (fgets(line, sizeof(line), queuef) == NULL || line[0] == 0)
			break;
		line[strlen(line) - 1] = 0;	/* chop newline */

		s = strchr(line, ':');
		if (s == NULL)
			goto malformed;
		*s = 0;

		s++;
		while (isspace(*s))
			s++;

		s = strdup(s);
		if (s == NULL)
			goto malformed;

		if (strcmp(line, "ID") == 0) {
			queueid = s;
		} else if (strcmp(line, "Sender") == 0) {
			sender = s;
		} else if (strcmp(line, "Recipient") == 0) {
			addr = s;
		} else {
			syslog(LOG_DEBUG, "ignoring unknown queue info `%s' in `%s'",
			       line, queuefn);
			free(s);
		}
	}

	if (queueid == NULL || sender == NULL || addr == NULL ||
	    *queueid == 0 || *addr == 0) {
malformed:
		errno = EINVAL;
		syslog(LOG_ERR, "malformed queue file `%s'", queuefn);
		goto out;
	}

	if (add_recp(&itmqueue, addr, 0) != 0)
		goto out;

	it = LIST_FIRST(&itmqueue.queue);
	it->sender = sender; sender = NULL;
	it->queueid = queueid; queueid = NULL;
	it->queuefn = queuefn; queuefn = NULL;
	LIST_INSERT_HEAD(&queue->queue, it, next);

out:
	if (sender != NULL)
		free(sender);
	if (queueid != NULL)
		free(queueid);
	if (addr != NULL)
		free(addr);
	if (queuef != NULL)
		fclose(queuef);

	return (it);
}