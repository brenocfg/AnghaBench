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
typedef  int /*<<< orphan*/  lck_grp_attr_t ;
typedef  int /*<<< orphan*/  lck_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPTAP_IFNAME ; 
 int /*<<< orphan*/  iptap_grp ; 
 int /*<<< orphan*/  iptap_lck_rw ; 
 int /*<<< orphan*/ * lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_attr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_attr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iptap_alloc_lock(void)
{
	lck_grp_attr_t *grp_attr;
	lck_attr_t *attr;
	
	grp_attr = lck_grp_attr_alloc_init();
	lck_grp_attr_setdefault(grp_attr);
	iptap_grp = lck_grp_alloc_init(IPTAP_IFNAME, grp_attr);
	lck_grp_attr_free(grp_attr);
	
	attr = lck_attr_alloc_init();
	lck_attr_setdefault(attr);
	
	lck_rw_init(&iptap_lck_rw, iptap_grp, attr);
	lck_attr_free(attr);
}