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
struct dm_target {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int build_constructor_string(struct dm_target *ti,
				    unsigned argc, char **argv,
				    char **ctr_str)
{
	int i, str_size;
	char *str = NULL;

	*ctr_str = NULL;

	for (i = 0, str_size = 0; i < argc; i++)
		str_size += strlen(argv[i]) + 1; /* +1 for space between args */

	str_size += 20; /* Max number of chars in a printed u64 number */

	str = kzalloc(str_size, GFP_KERNEL);
	if (!str) {
		DMWARN("Unable to allocate memory for constructor string");
		return -ENOMEM;
	}

	str_size = sprintf(str, "%llu", (unsigned long long)ti->len);
	for (i = 0; i < argc; i++)
		str_size += sprintf(str + str_size, " %s", argv[i]);

	*ctr_str = str;
	return str_size;
}