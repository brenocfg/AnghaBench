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
 int /*<<< orphan*/ * lck_grp_alloc_init (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_attr_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ lck_grp_t *
my_lck_grp_alloc_init(const char * grp_name)
{
    lck_grp_t *		grp;
    lck_grp_attr_t *	grp_attrs;
    
    grp_attrs = lck_grp_attr_alloc_init();
    grp = lck_grp_alloc_init(grp_name, grp_attrs);
    lck_grp_attr_free(grp_attrs);
    return (grp);
}