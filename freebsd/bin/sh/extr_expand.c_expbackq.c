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
typedef  union node {int dummy; } node ;
struct worddest {int dummy; } ;
struct backcmd {char* buf; scalar_t__ nleft; scalar_t__ fd; scalar_t__ jp; } ;

/* Variables and functions */
 char* BASESYNTAX ; 
 char const CCTL ; 
 int /*<<< orphan*/  CHECKSTRSPACE (int,char*) ; 
 char CTLESC ; 
 char* DQSYNTAX ; 
 scalar_t__ EINTR ; 
 int EXP_CASE ; 
 int EXP_GLOB ; 
 int EXP_SPLIT ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  NEXTWORD (char,int,char*,struct worddest*) ; 
 char STTOPC (char*) ; 
 int /*<<< orphan*/  STUNPUTC (char*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  USTPUTC (char,char*) ; 
 int /*<<< orphan*/  ckfree (char*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  evalbackcmd (union node*,struct backcmd*) ; 
 int /*<<< orphan*/  exitstatus ; 
 char* expdest ; 
 char* grabstackstr (char*) ; 
 scalar_t__ ifsset () ; 
 char* ifsval () ; 
 int read (scalar_t__,char*,int) ; 
 char* stackblock () ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  ungrabstackstr (char*,char*) ; 
 int /*<<< orphan*/  waitforjob (scalar_t__,int*) ; 

__attribute__((used)) static void
expbackq(union node *cmd, int quoted, int flag, struct worddest *dst)
{
	struct backcmd in;
	int i;
	char buf[128];
	char *p;
	char *dest = expdest;
	char lastc;
	char const *syntax = quoted? DQSYNTAX : BASESYNTAX;
	int quotes = flag & (EXP_GLOB | EXP_CASE);
	size_t nnl;
	const char *ifs;
	int startloc;

	INTOFF;
	p = grabstackstr(dest);
	evalbackcmd(cmd, &in);
	ungrabstackstr(p, dest);

	p = in.buf;
	startloc = dest - stackblock();
	nnl = 0;
	if (!quoted && flag & EXP_SPLIT)
		ifs = ifsset() ? ifsval() : " \t\n";
	else
		ifs = "";
	/* Remove trailing newlines */
	for (;;) {
		if (--in.nleft < 0) {
			if (in.fd < 0)
				break;
			while ((i = read(in.fd, buf, sizeof buf)) < 0 && errno == EINTR)
				;
			TRACE(("expbackq: read returns %d\n", i));
			if (i <= 0)
				break;
			p = buf;
			in.nleft = i - 1;
		}
		lastc = *p++;
		if (lastc == '\0')
			continue;
		if (nnl > 0 && lastc != '\n') {
			NEXTWORD('\n', flag, dest, dst);
			nnl = 0;
		}
		if (strchr(ifs, lastc) != NULL) {
			if (lastc == '\n')
				nnl++;
			else
				NEXTWORD(lastc, flag, dest, dst);
		} else {
			CHECKSTRSPACE(2, dest);
			if (quotes && syntax[(int)lastc] == CCTL)
				USTPUTC(CTLESC, dest);
			USTPUTC(lastc, dest);
		}
	}
	while (dest > stackblock() + startloc && STTOPC(dest) == '\n')
		STUNPUTC(dest);

	if (in.fd >= 0)
		close(in.fd);
	if (in.buf)
		ckfree(in.buf);
	if (in.jp) {
		p = grabstackstr(dest);
		exitstatus = waitforjob(in.jp, (int *)NULL);
		ungrabstackstr(p, dest);
	}
	TRACE(("expbackq: done\n"));
	expdest = dest;
	INTON;
}