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

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_cleanup () ; 
 int /*<<< orphan*/  fileno (scalar_t__) ; 
 scalar_t__ fopen (char*,char*) ; 
 scalar_t__ log_file ; 
 char* log_path ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pfd ; 
 int /*<<< orphan*/  print_d (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ specified_log_file ; 

void init_log(void)
{
	if (specified_log_file) {
		log_file = fopen(log_path, "a");
		if (!log_file)
			perror("Open log file failed");
		printf("Using specified log file %s\n\n", log_path);
	}

	if (!log_file) {
		log_file = fopen("demo.log", "a");
		if (!log_file) {
			perror("Open log file failed");
			exit_cleanup();
		} else {
			printf("Using default log file %s\n\n", "./demo.log");
		}
	}

	pfd = dup(STDERR_FILENO);

	dup2(fileno(log_file), STDOUT_FILENO);
	dup2(fileno(log_file), STDERR_FILENO);

	print_d("Log starts\n");
}