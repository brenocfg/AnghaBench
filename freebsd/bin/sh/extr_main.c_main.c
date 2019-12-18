#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stackmark {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_EXIT ; 
 scalar_t__ EXEXIT ; 
 scalar_t__ EXINT ; 
 int /*<<< orphan*/  FORCEINTON ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  chkmail (int) ; 
 int /*<<< orphan*/  cmdloop (int) ; 
 int /*<<< orphan*/  evalstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ exception ; 
 int /*<<< orphan*/  exitshell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exitstatus ; 
 int /*<<< orphan*/  getpid () ; 
 TYPE_1__* handler ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  initcharset () ; 
 int /*<<< orphan*/  initvar () ; 
 char* lookupvar (char*) ; 
 TYPE_1__ main_handler ; 
 int /*<<< orphan*/ * minusc ; 
 int /*<<< orphan*/  opentrace () ; 
 int /*<<< orphan*/  out2fmt_flush (char*) ; 
 int /*<<< orphan*/  popstackmark (struct stackmark*) ; 
 scalar_t__ privileged ; 
 int /*<<< orphan*/  procargs (int,char**) ; 
 int /*<<< orphan*/  pwd_init (scalar_t__) ; 
 int /*<<< orphan*/  read_profile (char*) ; 
 int /*<<< orphan*/  reset () ; 
 int /*<<< orphan*/  rootpid ; 
 int rootshell ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setstackmark (struct stackmark*) ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/  trargs (char**) ; 
 int /*<<< orphan*/  trputs (char*) ; 

int
main(int argc, char *argv[])
{
	struct stackmark smark, smark2;
	volatile int state;
	char *shinit;

	(void) setlocale(LC_ALL, "");
	initcharset();
	state = 0;
	if (setjmp(main_handler.loc)) {
		if (state == 0 || iflag == 0 || ! rootshell ||
		    exception == EXEXIT)
			exitshell(exitstatus);
		reset();
		if (exception == EXINT)
			out2fmt_flush("\n");
		popstackmark(&smark);
		FORCEINTON;				/* enable interrupts */
		if (state == 1)
			goto state1;
		else if (state == 2)
			goto state2;
		else if (state == 3)
			goto state3;
		else
			goto state4;
	}
	handler = &main_handler;
#ifdef DEBUG
	opentrace();
	trputs("Shell args:  ");  trargs(argv);
#endif
	rootpid = getpid();
	rootshell = 1;
	INTOFF;
	initvar();
	setstackmark(&smark);
	setstackmark(&smark2);
	procargs(argc, argv);
	pwd_init(iflag);
	INTON;
	if (iflag)
		chkmail(1);
	if (argv[0] && argv[0][0] == '-') {
		state = 1;
		read_profile("/etc/profile");
state1:
		state = 2;
		if (privileged == 0)
			read_profile("${HOME-}/.profile");
		else
			read_profile("/etc/suid_profile");
	}
state2:
	state = 3;
	if (!privileged && iflag) {
		if ((shinit = lookupvar("ENV")) != NULL && *shinit != '\0') {
			state = 3;
			read_profile(shinit);
		}
	}
state3:
	state = 4;
	popstackmark(&smark2);
	if (minusc) {
		evalstring(minusc, sflag ? 0 : EV_EXIT);
	}
state4:
	if (sflag || minusc == NULL) {
		cmdloop(1);
	}
	exitshell(exitstatus);
	/*NOTREACHED*/
	return 0;
}