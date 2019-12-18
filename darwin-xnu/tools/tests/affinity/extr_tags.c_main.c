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
typedef  int thread_act_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  err (int,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ geteuid () ; 
 int getopt (int,char**,char*) ; 
 char* input ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  mutter (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 scalar_t__ task_for_pid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ task_threads (int /*<<< orphan*/ ,int**,int*) ; 
 int thread_tag_get (int) ; 
 int /*<<< orphan*/  thread_tag_set (int,int) ; 
 int /*<<< orphan*/  usage () ; 
 void* verbosity ; 

int
main(int argc, char *argv[])
{
	kern_return_t		ret;
	mach_port_name_t	port;
	int			pid;
	int			c;
	thread_act_t		*thread_array;
	mach_msg_type_number_t	num_threads;
	int			i;
	boolean_t		interactive = FALSE;
	int			tag;

	if (geteuid() != 0) {
		printf("Must be run as root\n");
		exit(1);
	}

	/* Do switch parsing: */
	while ((c = getopt (argc, argv, "hiv:")) != -1) {
		switch (c) {
		case 'i':
			interactive = TRUE;
			break;
		case 'v':
			verbosity = atoi(optarg);
			break;
		case 'h':
		case '?':
		default:
			usage();
		}
	}
	argc -= optind; argv += optind;
	if (argc > 0)
		pid = atoi(*argv);

	ret = task_for_pid(mach_task_self(), pid, &port);
	if (ret != KERN_SUCCESS)
		err(1, "task_for_pid(,%d,) returned %d", pid, ret);	

	mutter("task %p\n", port);
	ret = task_threads(port, &thread_array, &num_threads);
	if (ret != KERN_SUCCESS)
		err(1, "task_threads() returned %d", pid, ret);	
 
	for (i = 0; i < num_threads; i++) {
		printf(" %d: thread 0x%08x tag %d\n",
			i, thread_array[i], thread_tag_get(thread_array[i]));
	}

	while (interactive) {
		printf("Enter new tag or <return> to skip or ^D to quit\n");
		for (i = 0; i < num_threads; i++) {
			tag =  thread_tag_get(thread_array[i]);
			printf(" %d: thread 0x%08x tag %d: ",
				i, thread_array[i], tag);
			fflush(stdout);
			(void) fgets(input, 20, stdin);
			if (feof(stdin)) {
				printf("\n");
				interactive = FALSE;
				break;
			}
			if (strlen(input) > 1) {
				tag = atoi(input);
				thread_tag_set(thread_array[i], tag);
			}
		}
	}

	return 0;
}