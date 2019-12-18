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
struct timeval {long tv_sec; long tv_usec; } ;
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; } ;
struct itimerval {struct timeval it_value; int /*<<< orphan*/  it_interval; } ;
typedef  int MMAL_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int MMAL_SUCCESS ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGALRM ; 
 int atoi (char const*) ; 
 int autosusp_signal ; 
 int /*<<< orphan*/  autosusp_timeout_handler ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmal_vc_release () ; 
 int mmal_vc_use () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usleep (long) ; 

__attribute__((used)) static int do_autosusptest(int argc, const char **argv)
{
   long timeout;
   struct timeval interval;
   MMAL_STATUS_T status;

   if (argc != 4)
   {
      printf("usage: %s autosusp <timeout-ms> <signal>\n",
             argv[0]);
      printf("   e.g. 650 9\n");
      exit(1);
   }
   timeout = 1000 * atoi(argv[2]);
   autosusp_signal = atoi(argv[3]);

   if ((status=mmal_vc_use()) != MMAL_SUCCESS)
   {
      fprintf(stderr,"mmal_vc_use failed: %d\n", status);
      exit(1);
   }

   /* install a signal handler for the alarm */
   struct sigaction sa;
   memset(&sa, 0, sizeof(struct sigaction));
   sa.sa_sigaction = autosusp_timeout_handler;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_SIGINFO;
   if (sigaction(SIGALRM, &sa, 0))
   {
      perror("sigaction");
      exit(1);
   }

   /* when to expire */
   interval.tv_sec = timeout / 1000000;
   interval.tv_usec = timeout % 1000000;

   struct itimerval alarm_spec = {
     .it_interval = {0,0},
     .it_value = interval
   };

   int rc = setitimer(ITIMER_REAL, &alarm_spec, NULL);
   if (rc < 0)
   {
      perror("setitimer failed");
      exit(1);
   }

   usleep(timeout + 1000000);
   printf("%s: not killed by timer\n", argv[0]);
   mmal_vc_release();

   return 0;
}