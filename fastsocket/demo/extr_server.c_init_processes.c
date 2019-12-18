#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct worker_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  process; scalar_t__ cpu_id; scalar_t__ trancnt; } ;

/* Variables and functions */
 int MAP_ANON ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_cleanup () ; 
 int fork () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int num_workers ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  process_clients (void*) ; 
 scalar_t__ start_cpu ; 
 TYPE_1__* wdata ; 

void init_processes(void)
{
	int i, pid;

	wdata = mmap(NULL, num_workers * sizeof(struct worker_data),
		     PROT_READ|PROT_WRITE,
		     MAP_ANON|MAP_SHARED,
		     -1, 0);

	memset(wdata, 0, num_workers * sizeof(struct worker_data));

	if (wdata == NULL) {
		perror("Unable to mmap shared global wdata");
		exit_cleanup();
	}

	for(i = 0; i < num_workers; i++) {
		wdata[i].trancnt = 0;
		wdata[i].cpu_id = i + start_cpu;

		if ( (pid = fork()) < 0) {
			perror("Unable to fork child process");
			exit_cleanup();
		} else if( pid == 0) {
			wdata[i].process = getpid();
			process_clients((void *)&(wdata[i]));
			exit(0);
		}
	}
}