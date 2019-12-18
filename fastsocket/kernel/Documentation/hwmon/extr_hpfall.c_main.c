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
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
typedef  int /*<<< orphan*/  count ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int EINVAL ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ignore_me ; 
 scalar_t__ lid_open () ; 
 int /*<<< orphan*/  mlockall (int) ; 
 scalar_t__ on_ac () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  protect (int) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  sched_get_priority_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  set_led (int) ; 
 int set_unload_heads_path (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  valid_disk () ; 

int main(int argc, char **argv)
{
	int fd, ret;
	struct sched_param param;

	if (argc == 1)
		ret = set_unload_heads_path("/dev/sda");
	else if (argc == 2)
		ret = set_unload_heads_path(argv[1]);
	else
		ret = -EINVAL;

	if (ret || !valid_disk()) {
		fprintf(stderr, "usage: %s <device> (default: /dev/sda)\n",
				argv[0]);
		exit(1);
	}

	fd = open("/dev/freefall", O_RDONLY);
	if (fd < 0) {
		perror("/dev/freefall");
		return EXIT_FAILURE;
	}

	daemon(0, 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	sched_setscheduler(0, SCHED_FIFO, &param);
	mlockall(MCL_CURRENT|MCL_FUTURE);

	signal(SIGALRM, ignore_me);

	for (;;) {
		unsigned char count;

		ret = read(fd, &count, sizeof(count));
		alarm(0);
		if ((ret == -1) && (errno == EINTR)) {
			/* Alarm expired, time to unpark the heads */
			continue;
		}

		if (ret != sizeof(count)) {
			perror("read");
			break;
		}

		protect(21);
		set_led(1);
		if (1 || on_ac() || lid_open())
			alarm(2);
		else
			alarm(20);
	}

	close(fd);
	return EXIT_SUCCESS;
}