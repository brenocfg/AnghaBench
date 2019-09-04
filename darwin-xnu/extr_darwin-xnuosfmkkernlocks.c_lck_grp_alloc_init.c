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
typedef  int /*<<< orphan*/  lck_grp_t ;
typedef  int /*<<< orphan*/  lck_grp_attr_t ;

/* Variables and functions */
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

lck_grp_t *
lck_grp_alloc_init(
	const char*	grp_name,
	lck_grp_attr_t	*attr)
{
	lck_grp_t	*grp;

	if ((grp = (lck_grp_t *)kalloc(sizeof(lck_grp_t))) != 0)
		lck_grp_init(grp, grp_name, attr);

	return(grp);
}