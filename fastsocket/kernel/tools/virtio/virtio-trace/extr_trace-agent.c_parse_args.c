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
struct agent_info {int use_stdout; unsigned long pipe_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  agent_info_init (struct agent_info*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 unsigned long parse_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static void *parse_args(int argc, char *argv[], struct agent_info *s)
{
	int cmd;
	unsigned long size;

	while ((cmd = getopt(argc, argv, "hos:")) != -1) {
		switch (cmd) {
		/* stdout mode */
		case 'o':
			s->use_stdout = true;
			break;
		/* size of pipe */
		case 's':
			size = parse_size(optarg);
			if (size == 0)
				goto error;
			s->pipe_size = size;
			break;
		case 'h':
		default:
			usage(argv[0]);
			goto error;
		}
	}

	agent_info_init(s);

	return NULL;

error:
	exit(EXIT_FAILURE);
}