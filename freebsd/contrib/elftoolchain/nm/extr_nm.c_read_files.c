#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* def_filename; } ;
struct TYPE_3__ {scalar_t__ print_name; } ;

/* Variables and functions */
 scalar_t__ PRINT_NAME_MULTI ; 
 scalar_t__ PRINT_NAME_NONE ; 
 TYPE_2__ nm_info ; 
 TYPE_1__ nm_opts ; 
 int read_object (char*) ; 

__attribute__((used)) static int
read_files(int argc, char **argv)
{
	int rtn = 0;

	if (argc < 0 || argv == NULL)
		return (1);

	if (argc == 0)
		rtn |= read_object(nm_info.def_filename);
	else {
		if (nm_opts.print_name == PRINT_NAME_NONE && argc > 1)
			nm_opts.print_name = PRINT_NAME_MULTI;
		while (argc > 0) {
			rtn |= read_object(*argv);
			--argc;
			++argv;
		}
	}

	return (rtn);
}