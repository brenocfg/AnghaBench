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
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  lck_grp_t ;
typedef  int /*<<< orphan*/  lck_attr_t ;

/* Variables and functions */
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_zone ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

lck_mtx_t *
lck_mtx_alloc_init(
	lck_grp_t	*grp,
	lck_attr_t	*attr)
{
	lck_mtx_t	*lck;
#ifdef	MUTEX_ZONE
	if ((lck = (lck_mtx_t *)zalloc(lck_mtx_zone)) != 0)
		lck_mtx_init(lck, grp, attr);
#else
	if ((lck = (lck_mtx_t *)kalloc(sizeof(lck_mtx_t))) != 0)
		lck_mtx_init(lck, grp, attr);
#endif		
	return(lck);
}