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
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
struct rlimit {int /*<<< orphan*/  rlim_max; int /*<<< orphan*/  rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_DATA ; 
 int /*<<< orphan*/  RLIMIT_FSIZE ; 
 int /*<<< orphan*/  RLIMIT_RSS ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGXCPU ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int /*<<< orphan*/  s_mask ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 scalar_t__ setup_sig (int /*<<< orphan*/ ,struct sigaction*) ; 
 int /*<<< orphan*/  sig_cleanup ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 scalar_t__ sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
gen_init(void)
{
	struct rlimit reslimit;
	struct sigaction n_hand;

	/*
	 * Really needed to handle large archives. We can run out of memory for
	 * internal tables really fast when we have a whole lot of files...
	 */
	if (getrlimit(RLIMIT_DATA , &reslimit) == 0){
		reslimit.rlim_cur = reslimit.rlim_max;
		(void)setrlimit(RLIMIT_DATA , &reslimit);
	}

	/*
	 * should file size limits be waived? if the os limits us, this is
	 * needed if we want to write a large archive
	 */
	if (getrlimit(RLIMIT_FSIZE , &reslimit) == 0){
		reslimit.rlim_cur = reslimit.rlim_max;
		(void)setrlimit(RLIMIT_FSIZE , &reslimit);
	}

	/*
	 * increase the size the stack can grow to
	 */
	if (getrlimit(RLIMIT_STACK , &reslimit) == 0){
		reslimit.rlim_cur = reslimit.rlim_max;
		(void)setrlimit(RLIMIT_STACK , &reslimit);
	}

	/*
	 * not really needed, but doesn't hurt
	 */
	if (getrlimit(RLIMIT_RSS , &reslimit) == 0){
		reslimit.rlim_cur = reslimit.rlim_max;
		(void)setrlimit(RLIMIT_RSS , &reslimit);
	}

	/*
	 * signal handling to reset stored directory times and modes. Since
	 * we deal with broken pipes via failed writes we ignore it. We also
	 * deal with any file size limit thorough failed writes. Cpu time
	 * limits are caught and a cleanup is forced.
	 */
	if ((sigemptyset(&s_mask) < 0) || (sigaddset(&s_mask, SIGTERM) < 0) ||
	    (sigaddset(&s_mask,SIGINT) < 0)||(sigaddset(&s_mask,SIGHUP) < 0) ||
	    (sigaddset(&s_mask,SIGPIPE) < 0)||(sigaddset(&s_mask,SIGQUIT)<0) ||
	    (sigaddset(&s_mask,SIGXCPU) < 0)||(sigaddset(&s_mask,SIGXFSZ)<0)) {
		paxwarn(1, "Unable to set up signal mask");
		return(-1);
	}
	memset(&n_hand, 0, sizeof n_hand);
	n_hand.sa_mask = s_mask;
	n_hand.sa_flags = 0;
	n_hand.sa_handler = sig_cleanup;

	if (setup_sig(SIGHUP,  &n_hand) ||
	   setup_sig(SIGTERM, &n_hand) ||
	   setup_sig(SIGINT,  &n_hand) ||
	   setup_sig(SIGQUIT, &n_hand) ||
	   setup_sig(SIGXCPU, &n_hand))
		goto out;

	n_hand.sa_handler = SIG_IGN;
	if ((sigaction(SIGPIPE, &n_hand, NULL) < 0) ||
	    (sigaction(SIGXFSZ, &n_hand, NULL) < 0))
		goto out;
	return(0);

    out:
	syswarn(1, errno, "Unable to set up signal handler");
	return(-1);
}