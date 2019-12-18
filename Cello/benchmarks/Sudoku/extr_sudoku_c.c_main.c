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
typedef  int /*<<< orphan*/  sdaux_t ;

/* Variables and functions */
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sd_genmat () ; 
 int /*<<< orphan*/  sd_solve (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

int main()
{
	sdaux_t *a = sd_genmat();
	char buf[1024];
	while (fgets(buf, 1024, stdin) != 0) {
		if (strlen(buf) < 81) continue;
		sd_solve(a, buf);
		//putchar('\n');
	}
	free(a);
	return 0;
}