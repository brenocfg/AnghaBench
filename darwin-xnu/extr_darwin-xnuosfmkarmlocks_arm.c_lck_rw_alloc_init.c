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
typedef  int /*<<< orphan*/  lck_attr_t ;

/* Variables and functions */
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  lck_rw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

lck_rw_t *
lck_rw_alloc_init(
	lck_grp_t	*grp,
	lck_attr_t	*attr)
{
	lck_rw_t	*lck;

	if ((lck = (lck_rw_t *)kalloc(sizeof(lck_rw_t))) != 0)
		lck_rw_init(lck, grp, attr);

	return lck;
}