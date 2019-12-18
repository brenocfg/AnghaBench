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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ geteuid () ; 

__attribute__((used)) static bool symbol__read_kptr_restrict(void)
{
	bool value = false;

	if (geteuid() != 0) {
		FILE *fp = fopen("/proc/sys/kernel/kptr_restrict", "r");
		if (fp != NULL) {
			char line[8];

			if (fgets(line, sizeof(line), fp) != NULL)
				value = atoi(line) != 0;

			fclose(fp);
		}
	}

	return value;
}