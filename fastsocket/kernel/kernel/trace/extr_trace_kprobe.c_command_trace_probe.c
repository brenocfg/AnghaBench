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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  argv_free (char**) ; 
 char** argv_split (int /*<<< orphan*/ ,char const*,int*) ; 
 int create_trace_probe (int,char**) ; 

__attribute__((used)) static int command_trace_probe(const char *buf)
{
	char **argv;
	int argc = 0, ret = 0;

	argv = argv_split(GFP_KERNEL, buf, &argc);
	if (!argv)
		return -ENOMEM;

	if (argc)
		ret = create_trace_probe(argc, argv);

	argv_free(argv);
	return ret;
}