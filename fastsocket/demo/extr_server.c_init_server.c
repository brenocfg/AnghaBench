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
typedef  int /*<<< orphan*/  uint16_t ;
struct rlimit {void* rlim_max; void* rlim_cur; } ;
struct in_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  listen_fd; int /*<<< orphan*/  param_port; struct in_addr listenip; } ;

/* Variables and functions */
 void* MAX_CONNS_PER_WORKER ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 void* RLIM_INFINITY ; 
 int /*<<< orphan*/  exit_cleanup () ; 
 int /*<<< orphan*/  getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  init_single_server (struct in_addr,int /*<<< orphan*/ ) ; 
 TYPE_1__* la ; 
 int la_num ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_d (char*,void*,void*) ; 
 int setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

void init_server(void)
{
	int ret, i;
	struct rlimit limits;

	for (i = 0; i < la_num; i++){
		struct in_addr ip;
		uint16_t port;

		ip = la[i].listenip;
		port = la[i].param_port;

		la[i].listen_fd = init_single_server(ip, port);
	}

	limits.rlim_cur = RLIM_INFINITY;
	limits.rlim_max = RLIM_INFINITY;

	ret = setrlimit(RLIMIT_CORE, &limits);
	if (ret < 0) {
		perror("Set core limit failed");
		exit_cleanup();
	}

	getrlimit(RLIMIT_CORE, &limits);
	print_d("Core limit %ld %ld\n", limits.rlim_cur, limits.rlim_max);

	limits.rlim_cur = MAX_CONNS_PER_WORKER;
	limits.rlim_max = MAX_CONNS_PER_WORKER;

	ret = setrlimit(RLIMIT_NOFILE, &limits);
	if (ret < 0) {
		perror("Set open file limit failed");
		exit_cleanup();
	}

	getrlimit(RLIMIT_NOFILE, &limits);
	print_d("Open file limit %ld %ld\n", limits.rlim_cur, limits.rlim_max);
}