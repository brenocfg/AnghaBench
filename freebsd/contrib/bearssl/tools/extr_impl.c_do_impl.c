#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ br_config_option ;

/* Variables and functions */
 TYPE_1__* br_get_config () ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 

int
do_impl(int argc, char *argv[])
{
	const br_config_option *opt;

	(void)argc;
	(void)argv;

	for (opt = br_get_config(); opt->name != NULL; opt ++) {
		printf("%-25s %8ld\n", opt->name, opt->value);
	}

	return 0;
}