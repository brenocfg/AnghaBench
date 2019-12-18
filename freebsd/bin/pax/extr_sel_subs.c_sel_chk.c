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
typedef  int /*<<< orphan*/  ARCHD ;

/* Variables and functions */
 scalar_t__ grp_match (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * grptb ; 
 int /*<<< orphan*/ * trhead ; 
 scalar_t__ trng_match (int /*<<< orphan*/ *) ; 
 scalar_t__ usr_match (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * usrtb ; 

int
sel_chk(ARCHD *arcn)
{
	if (((usrtb != NULL) && usr_match(arcn)) ||
	    ((grptb != NULL) && grp_match(arcn)) ||
	    ((trhead != NULL) && trng_match(arcn)))
		return(1);
	return(0);
}