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
struct compressor_pager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Z_CALLERACCT ; 
 int /*<<< orphan*/  Z_NOENCRYPT ; 
 int /*<<< orphan*/  compressor_pager_lck_attr ; 
 int /*<<< orphan*/  compressor_pager_lck_grp ; 
 int /*<<< orphan*/  compressor_pager_lck_grp_attr ; 
 int /*<<< orphan*/  compressor_pager_zone ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_compressor_init () ; 
 int /*<<< orphan*/  zinit (int,int,int,char*) ; 
 int /*<<< orphan*/  zone_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_compressor_pager_init(void)
{
	lck_grp_attr_setdefault(&compressor_pager_lck_grp_attr);
	lck_grp_init(&compressor_pager_lck_grp, "compressor_pager", &compressor_pager_lck_grp_attr);
	lck_attr_setdefault(&compressor_pager_lck_attr);

	compressor_pager_zone = zinit(sizeof (struct compressor_pager),
				      10000 * sizeof (struct compressor_pager),
				      8192, "compressor_pager");
	zone_change(compressor_pager_zone, Z_CALLERACCT, FALSE);
	zone_change(compressor_pager_zone, Z_NOENCRYPT, TRUE);

	vm_compressor_init();
}