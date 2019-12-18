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
typedef  int /*<<< orphan*/  DEVT ;

/* Variables and functions */
 int /*<<< orphan*/  D_TAB_SZ ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** dtab ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 

int
dev_start(void)
{
	if (dtab != NULL)
		return(0);
 	if ((dtab = (DEVT **)calloc(D_TAB_SZ, sizeof(DEVT *))) == NULL) {
		paxwarn(1, "Cannot allocate memory for device mapping table");
		return(-1);
	}
	return(0);
}