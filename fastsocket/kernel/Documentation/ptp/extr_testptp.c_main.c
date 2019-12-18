#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tx ;
typedef  int /*<<< orphan*/  timer_t ;
typedef  int /*<<< orphan*/  timeout ;
struct TYPE_10__ {int nsec; scalar_t__ sec; } ;
struct TYPE_9__ {int sec; scalar_t__ nsec; } ;
struct TYPE_8__ {int tv_sec; } ;
struct TYPE_7__ {int tv_sec; } ;
struct TYPE_11__ {int tv_sec; scalar_t__ tv_usec; } ;
struct timex {TYPE_4__ period; TYPE_3__ start; scalar_t__ index; TYPE_2__ it_value; TYPE_1__ it_interval; scalar_t__ flags; TYPE_5__ time; int /*<<< orphan*/  modes; int /*<<< orphan*/  freq; } ;
struct timespec {int tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct sigevent {void* sigev_signo; void* sigev_notify; } ;
struct ptp_perout_request {TYPE_4__ period; TYPE_3__ start; scalar_t__ index; TYPE_2__ it_value; TYPE_1__ it_interval; scalar_t__ flags; TYPE_5__ time; int /*<<< orphan*/  modes; int /*<<< orphan*/  freq; } ;
struct ptp_extts_request {TYPE_4__ period; TYPE_3__ start; scalar_t__ index; TYPE_2__ it_value; TYPE_1__ it_interval; scalar_t__ flags; TYPE_5__ time; int /*<<< orphan*/  modes; int /*<<< orphan*/  freq; } ;
struct TYPE_12__ {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; } ;
struct ptp_extts_event {int index; TYPE_6__ t; } ;
struct ptp_clock_caps {int max_adj; int n_alarm; int n_ext_ts; int n_per_out; int pps; } ;
struct itimerspec {TYPE_4__ period; TYPE_3__ start; scalar_t__ index; TYPE_2__ it_value; TYPE_1__ it_interval; scalar_t__ flags; TYPE_5__ time; int /*<<< orphan*/  modes; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  perout_request ;
typedef  int /*<<< orphan*/  extts_request ;
typedef  int /*<<< orphan*/  event ;
typedef  scalar_t__ clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_FREQUENCY ; 
 int /*<<< orphan*/  ADJ_SETOFFSET ; 
 scalar_t__ CLOCK_INVALID ; 
 scalar_t__ CLOCK_REALTIME ; 
 char* DEVICE ; 
 int EOF ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PTP_CLOCK_GETCAPS ; 
 scalar_t__ PTP_ENABLE_FEATURE ; 
 int /*<<< orphan*/  PTP_ENABLE_PPS ; 
 int /*<<< orphan*/  PTP_EXTTS_REQUEST ; 
 int /*<<< orphan*/  PTP_PEROUT_REQUEST ; 
 void* SIGALRM ; 
 void* SIGEV_SIGNAL ; 
 int atoi (char*) ; 
 scalar_t__ clock_adjtime (scalar_t__,struct timex*) ; 
 scalar_t__ clock_gettime (scalar_t__,struct timespec*) ; 
 scalar_t__ clock_settime (scalar_t__,struct timespec*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ctime (int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_clockid (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handle_alarm ; 
 int /*<<< orphan*/  install_handler (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memset (struct timex*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int /*<<< orphan*/  pause () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  ppb_to_scaled_ppm (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int read (int,struct ptp_extts_event*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ timer_create (scalar_t__,struct sigevent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_delete (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timex*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
	struct ptp_clock_caps caps;
	struct ptp_extts_event event;
	struct ptp_extts_request extts_request;
	struct ptp_perout_request perout_request;
	struct timespec ts;
	struct timex tx;

	static timer_t timerid;
	struct itimerspec timeout;
	struct sigevent sigevent;

	char *progname;
	int c, cnt, fd;

	char *device = DEVICE;
	clockid_t clkid;
	int adjfreq = 0x7fffffff;
	int adjtime = 0;
	int capabilities = 0;
	int extts = 0;
	int gettime = 0;
	int oneshot = 0;
	int periodic = 0;
	int perout = -1;
	int pps = -1;
	int settime = 0;

	progname = strrchr(argv[0], '/');
	progname = progname ? 1+progname : argv[0];
	while (EOF != (c = getopt(argc, argv, "a:A:cd:e:f:ghp:P:sSt:v"))) {
		switch (c) {
		case 'a':
			oneshot = atoi(optarg);
			break;
		case 'A':
			periodic = atoi(optarg);
			break;
		case 'c':
			capabilities = 1;
			break;
		case 'd':
			device = optarg;
			break;
		case 'e':
			extts = atoi(optarg);
			break;
		case 'f':
			adjfreq = atoi(optarg);
			break;
		case 'g':
			gettime = 1;
			break;
		case 'p':
			perout = atoi(optarg);
			break;
		case 'P':
			pps = atoi(optarg);
			break;
		case 's':
			settime = 1;
			break;
		case 'S':
			settime = 2;
			break;
		case 't':
			adjtime = atoi(optarg);
			break;
		case 'h':
			usage(progname);
			return 0;
		case '?':
		default:
			usage(progname);
			return -1;
		}
	}

	fd = open(device, O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "opening %s: %s\n", device, strerror(errno));
		return -1;
	}

	clkid = get_clockid(fd);
	if (CLOCK_INVALID == clkid) {
		fprintf(stderr, "failed to read clock id\n");
		return -1;
	}

	if (capabilities) {
		if (ioctl(fd, PTP_CLOCK_GETCAPS, &caps)) {
			perror("PTP_CLOCK_GETCAPS");
		} else {
			printf("capabilities:\n"
			       "  %d maximum frequency adjustment (ppb)\n"
			       "  %d programmable alarms\n"
			       "  %d external time stamp channels\n"
			       "  %d programmable periodic signals\n"
			       "  %d pulse per second\n",
			       caps.max_adj,
			       caps.n_alarm,
			       caps.n_ext_ts,
			       caps.n_per_out,
			       caps.pps);
		}
	}

	if (0x7fffffff != adjfreq) {
		memset(&tx, 0, sizeof(tx));
		tx.modes = ADJ_FREQUENCY;
		tx.freq = ppb_to_scaled_ppm(adjfreq);
		if (clock_adjtime(clkid, &tx)) {
			perror("clock_adjtime");
		} else {
			puts("frequency adjustment okay");
		}
	}

	if (adjtime) {
		memset(&tx, 0, sizeof(tx));
		tx.modes = ADJ_SETOFFSET;
		tx.time.tv_sec = adjtime;
		tx.time.tv_usec = 0;
		if (clock_adjtime(clkid, &tx) < 0) {
			perror("clock_adjtime");
		} else {
			puts("time shift okay");
		}
	}

	if (gettime) {
		if (clock_gettime(clkid, &ts)) {
			perror("clock_gettime");
		} else {
			printf("clock time: %ld.%09ld or %s",
			       ts.tv_sec, ts.tv_nsec, ctime(&ts.tv_sec));
		}
	}

	if (settime == 1) {
		clock_gettime(CLOCK_REALTIME, &ts);
		if (clock_settime(clkid, &ts)) {
			perror("clock_settime");
		} else {
			puts("set time okay");
		}
	}

	if (settime == 2) {
		clock_gettime(clkid, &ts);
		if (clock_settime(CLOCK_REALTIME, &ts)) {
			perror("clock_settime");
		} else {
			puts("set time okay");
		}
	}

	if (extts) {
		memset(&extts_request, 0, sizeof(extts_request));
		extts_request.index = 0;
		extts_request.flags = PTP_ENABLE_FEATURE;
		if (ioctl(fd, PTP_EXTTS_REQUEST, &extts_request)) {
			perror("PTP_EXTTS_REQUEST");
			extts = 0;
		} else {
			puts("external time stamp request okay");
		}
		for (; extts; extts--) {
			cnt = read(fd, &event, sizeof(event));
			if (cnt != sizeof(event)) {
				perror("read");
				break;
			}
			printf("event index %u at %lld.%09u\n", event.index,
			       event.t.sec, event.t.nsec);
			fflush(stdout);
		}
		/* Disable the feature again. */
		extts_request.flags = 0;
		if (ioctl(fd, PTP_EXTTS_REQUEST, &extts_request)) {
			perror("PTP_EXTTS_REQUEST");
		}
	}

	if (oneshot) {
		install_handler(SIGALRM, handle_alarm);
		/* Create a timer. */
		sigevent.sigev_notify = SIGEV_SIGNAL;
		sigevent.sigev_signo = SIGALRM;
		if (timer_create(clkid, &sigevent, &timerid)) {
			perror("timer_create");
			return -1;
		}
		/* Start the timer. */
		memset(&timeout, 0, sizeof(timeout));
		timeout.it_value.tv_sec = oneshot;
		if (timer_settime(timerid, 0, &timeout, NULL)) {
			perror("timer_settime");
			return -1;
		}
		pause();
		timer_delete(timerid);
	}

	if (periodic) {
		install_handler(SIGALRM, handle_alarm);
		/* Create a timer. */
		sigevent.sigev_notify = SIGEV_SIGNAL;
		sigevent.sigev_signo = SIGALRM;
		if (timer_create(clkid, &sigevent, &timerid)) {
			perror("timer_create");
			return -1;
		}
		/* Start the timer. */
		memset(&timeout, 0, sizeof(timeout));
		timeout.it_interval.tv_sec = periodic;
		timeout.it_value.tv_sec = periodic;
		if (timer_settime(timerid, 0, &timeout, NULL)) {
			perror("timer_settime");
			return -1;
		}
		while (1) {
			pause();
		}
		timer_delete(timerid);
	}

	if (perout >= 0) {
		if (clock_gettime(clkid, &ts)) {
			perror("clock_gettime");
			return -1;
		}
		memset(&perout_request, 0, sizeof(perout_request));
		perout_request.index = 0;
		perout_request.start.sec = ts.tv_sec + 2;
		perout_request.start.nsec = 0;
		perout_request.period.sec = 0;
		perout_request.period.nsec = perout;
		if (ioctl(fd, PTP_PEROUT_REQUEST, &perout_request)) {
			perror("PTP_PEROUT_REQUEST");
		} else {
			puts("periodic output request okay");
		}
	}

	if (pps != -1) {
		int enable = pps ? 1 : 0;
		if (ioctl(fd, PTP_ENABLE_PPS, enable)) {
			perror("PTP_ENABLE_PPS");
		} else {
			puts("pps for system time request okay");
		}
	}

	close(fd);
	return 0;
}