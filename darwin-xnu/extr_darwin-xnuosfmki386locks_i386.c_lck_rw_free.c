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
typedef  int /*<<< orphan*/  lck_rw_t ;
typedef  int /*<<< orphan*/  lck_grp_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lck_rw_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
lck_rw_free(
	lck_rw_t	*lck,
	lck_grp_t	*grp) {
	lck_rw_destroy(lck, grp);
	kfree(lck, sizeof(lck_rw_t));
}