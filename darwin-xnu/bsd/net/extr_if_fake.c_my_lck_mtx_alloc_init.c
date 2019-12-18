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
 int /*<<< orphan*/ * lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_attr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_mtx_alloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline lck_mtx_t *
my_lck_mtx_alloc_init(lck_grp_t * lck_grp)
{
	lck_attr_t * 	lck_attrs;
	lck_mtx_t *		lck_mtx;

	lck_attrs = lck_attr_alloc_init();
	lck_mtx = lck_mtx_alloc_init(lck_grp, lck_attrs);
	lck_attr_free(lck_attrs);
	return (lck_mtx);
}