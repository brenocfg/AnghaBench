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
typedef  int /*<<< orphan*/  lck_spin_t ;
typedef  int /*<<< orphan*/  lck_grp_t ;
typedef  int /*<<< orphan*/  lck_attr_t ;

/* Variables and functions */
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  lck_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

lck_spin_t     *
lck_spin_alloc_init(
		lck_grp_t * grp,
		lck_attr_t * attr)
{
	lck_spin_t     *lck;

	if ((lck = (lck_spin_t *) kalloc(sizeof(lck_spin_t))) != 0)
		lck_spin_init(lck, grp, attr);

	return (lck);
}