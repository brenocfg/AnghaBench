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
struct TYPE_2__ {char* name; int /*<<< orphan*/  (* fn ) () ;} ;

/* Variables and functions */
 scalar_t__ eq_name (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__* tfns ; 

int
main(int argc, char *argv[])
{
	size_t u;

	if (argc <= 1) {
		printf("usage: testcrypto all | name...\n");
		printf("individual test names:\n");
		for (u = 0; tfns[u].name; u ++) {
			printf("   %s\n", tfns[u].name);
		}
	} else {
		for (u = 0; tfns[u].name; u ++) {
			int i;

			for (i = 1; i < argc; i ++) {
				if (eq_name(argv[i], tfns[u].name)
					|| eq_name(argv[i], "all"))
				{
					tfns[u].fn();
					break;
				}
			}
		}
	}
	return 0;
}