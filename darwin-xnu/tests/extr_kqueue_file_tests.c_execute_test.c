#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int ident; scalar_t__ filter; } ;
struct TYPE_11__ {TYPE_6__ tu_kev; int /*<<< orphan*/  tu_pollevents; } ;
struct TYPE_10__ {int act_fd; } ;
struct TYPE_12__ {int t_testname; scalar_t__ t_nbytes; scalar_t__ t_known_failure; scalar_t__ t_nondeterministic; TYPE_2__ t_union; scalar_t__ t_is_poll_test; scalar_t__ t_want_event; int /*<<< orphan*/  t_n_cleanup_actions; int /*<<< orphan*/  t_cleanup_actions; int /*<<< orphan*/  t_watchfile; scalar_t__ t_file_is_fifo; scalar_t__ t_extra_sleep_hack; TYPE_1__ t_helpthreadact; scalar_t__ t_write_some_data; scalar_t__ t_read_to_end_first; int /*<<< orphan*/  t_n_prep_actions; int /*<<< orphan*/  t_prep_actions; } ;
typedef  TYPE_3__ test_t ;
struct timespec {long member_1; int /*<<< orphan*/  member_0; } ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
struct kevent {int flags; int data; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  evlist ;
struct TYPE_13__ {int act_fd; } ;
typedef  TYPE_4__ action_t ;

/* Variables and functions */
 scalar_t__ EVFILT_READ ; 
 scalar_t__ EVFILT_WRITE ; 
 int EV_ERROR ; 
 int /*<<< orphan*/  NOSLEEP ; 
 int O_RDONLY ; 
 int O_SYMLINK ; 
 int /*<<< orphan*/  T_EXPECTFAIL ; 
 int /*<<< orphan*/  T_FAIL (char*,int) ; 
 int /*<<< orphan*/  T_LOG (char*,...) ; 
 int /*<<< orphan*/  T_MAYFAIL ; 
 int /*<<< orphan*/  T_PASS (char*,int) ; 
 int /*<<< orphan*/  USLEEP_TIME ; 
 int /*<<< orphan*/  WAIT_TIME ; 
 int /*<<< orphan*/  WRITEFD ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  execute_action (TYPE_4__*) ; 
 int execute_action_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_action (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kevent (int,TYPE_6__*,int,struct kevent*,int,struct timespec*) ; 
 int kqueue () ; 
 int /*<<< orphan*/  memset (struct kevent*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  open_fifo (int /*<<< orphan*/ ,int*,int*) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (TYPE_4__*),void*) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  read_to_end (int) ; 
 int strerror (int) ; 
 scalar_t__ thread_status ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 

int
execute_test(test_t *test)
{
	int i, kqfd, filefd = -1, res2, res, cnt, writefd = -1;
	int retval = -1;
	pthread_t thr;
	struct kevent evlist;
	struct timespec ts = {WAIT_TIME, 0l};
	int *status;

	memset(&evlist, 0, sizeof(evlist));
	
	T_LOG("[BEGIN] %s\n", test->t_testname);

	T_LOG(test->t_want_event ? "Expecting an event.\n" : "Not expecting events.\n");
	
	res = execute_action_list(test->t_prep_actions, test->t_n_prep_actions, 1);
	
	/* If prep succeeded */
	if (0 == res) {
		/* Create kqueue for kqueue tests*/
		if (!test->t_is_poll_test) {
			if ((kqfd = kqueue()) == -1) {
				T_LOG("kqueue() failed: %d (%s)\n", errno, strerror(errno));
			}
		}
		
		if ((test->t_is_poll_test) || kqfd >= 0) {
			
			/* Open the file we're to monitor.  Fifos get special handling */
			if (test->t_file_is_fifo) {
				filefd = -1;
				open_fifo(test->t_watchfile, &filefd, &writefd);
			} else {
				if ((filefd = open(test->t_watchfile, O_RDONLY | O_SYMLINK)) == -1) {
					T_LOG("open() of watchfile %s failed: %d (%s)\n", test->t_watchfile,
					      errno, strerror(errno));
				}
			}
			
			if (filefd >= 0) {
				T_LOG("Opened file to monitor.\n");
				
				/* 
				 * Fill in the fd to monitor once you know it 
				 * If it's a fifo test, then the helper is definitely going to want the write end.
				 */
				test->t_helpthreadact.act_fd = (writefd >= 0 ? writefd : filefd);
				
				if (test->t_read_to_end_first) {
					read_to_end(filefd);
				} else if (test->t_write_some_data) {
					action_t dowr;
					init_action(&dowr, NOSLEEP, WRITEFD, 0);
					dowr.act_fd = writefd;
					(void)execute_action(&dowr);
				}
				
				/* Helper modifies the file that we're listening on (sleeps first, in general) */
				thread_status = 0;
				res = pthread_create(&thr, NULL, execute_action, (void*) &test->t_helpthreadact);
				if (0 == res) {
					T_LOG("Created helper thread.\n");
					
					/* This is ugly business to hack on filling up a FIFO */
					if (test->t_extra_sleep_hack) {
						usleep(USLEEP_TIME);
					}
					
					if (test->t_is_poll_test) {
						struct pollfd pl;
						pl.fd = filefd;
						pl.events = test->t_union.tu_pollevents;
						cnt = poll(&pl, 1, WAIT_TIME);
						T_LOG("Finished poll() call.\n");
						if ((cnt < 0)) {
							T_LOG("error is in errno, %s\n", strerror(errno));
							res = cnt;
						}
					} else {
						test->t_union.tu_kev.ident = filefd; 
						cnt = kevent(kqfd, &test->t_union.tu_kev, 1, &evlist, 1,  &ts);
						T_LOG("Finished kevent() call.\n");
						
						if ((cnt < 0) || (evlist.flags & EV_ERROR))  {
							T_LOG("kevent() call failed.\n");
							if (cnt < 0) {
								T_LOG("error is in errno, %s\n", strerror(errno));
							} else {
								T_LOG("error is in data, %s\n", strerror(evlist.data));
							}
							res = cnt;
						}
					}
					
					/* Success only if you've succeeded to this point AND joined AND other thread is happy*/
					status = NULL;
					res2 = pthread_join(thr, (void **)&status);
					if (res2 != 0) {
						T_LOG("Couldn't join helper thread: %d (%s).\n", res2,
							strerror(res2));
					} else if (*status) {
						T_LOG("Helper action had result %d\n", *status);
					}
					res = ((res == 0) && (res2 == 0) && (*status == 0)) ? 0 : -1;
				} else {
					T_LOG("Couldn't start thread: %d (%s).\n", res, strerror(res));
				}
				
				close(filefd);
				if (test->t_file_is_fifo) {
					close(writefd);
				}
			} else {
				T_LOG("Couldn't open test file %s to monitor: %d (%s)\n", test->t_watchfile);
				res = -1;
			}
			if (!test->t_is_poll_test) {
				close(kqfd);
			}
		} else {
			T_LOG("Couldn't open kqueue.\n");
			res = -1;
		}
	}
	
	/* Cleanup work */
	execute_action_list(test->t_cleanup_actions, test->t_n_cleanup_actions, 0);
	
	/* Success if nothing failed and we either received or did not receive event,
	 * as expected 
	 */
	if (0 == res) {
		T_LOG(cnt > 0 ? "Got an event.\n" : "Did not get an event.\n");
		if (((cnt > 0) && (test->t_want_event)) || ((cnt == 0) && (!test->t_want_event))) {
			if ((!test->t_is_poll_test) && (test->t_union.tu_kev.filter == EVFILT_READ || test->t_union.tu_kev.filter == EVFILT_WRITE)
				&& (test->t_nbytes) && (test->t_nbytes != evlist.data)) {
				T_LOG("Read wrong number of bytes available.  Wanted %d, got %d\n", test->t_nbytes, evlist.data);
				retval = -1;
			} else {
				retval = 0;
			}
			
		} else {
			T_LOG("Got unexpected event or lack thereof.\n");
			retval = -1;
		}
	} else {
		T_LOG("Failed to execute test. res = %d\n", res);
		retval = -1;
	}

	if (test->t_nondeterministic) {
		T_LOG("XXX non-deterministic test result = %d (%s)\n", retval,
			(retval == 0) ? "pass" : "fail");
		T_MAYFAIL;
	} else {
		if (test->t_known_failure) {
			// Signal to harness that this test is expected to fail.
			T_EXPECTFAIL;
		}
	}

	if (retval == 0) {
		T_PASS("%s", test->t_testname);
	} else {
		T_FAIL("%s", test->t_testname);
	}

	T_LOG("Test %s done with result %d.\n", test->t_testname, retval);
	return (retval);
}