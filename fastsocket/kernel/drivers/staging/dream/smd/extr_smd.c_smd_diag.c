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
 int /*<<< orphan*/  ID_DIAG_ERR_MSG ; 
 int SZ_DIAG_ERR_MSG ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 char* smem_find (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smd_diag(void)
{
	char *x;

	x = smem_find(ID_DIAG_ERR_MSG, SZ_DIAG_ERR_MSG);
	if (x != 0) {
		x[SZ_DIAG_ERR_MSG - 1] = 0;
		pr_info("smem: DIAG '%s'\n", x);
	}
}