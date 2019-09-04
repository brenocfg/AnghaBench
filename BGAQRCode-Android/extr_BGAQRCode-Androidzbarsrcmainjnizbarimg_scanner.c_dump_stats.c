#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int stat_iscn_syms_inuse; int stat_img_syms_inuse; int /*<<< orphan*/ * stat_sym_recycle; int /*<<< orphan*/  stat_sym_new; int /*<<< orphan*/  stat_img_syms_recycle; int /*<<< orphan*/  stat_iscn_syms_recycle; int /*<<< orphan*/  stat_syms_new; } ;
typedef  TYPE_1__ zbar_image_scanner_t ;

/* Variables and functions */
 int RECYCLE_BUCKETS ; 
 int /*<<< orphan*/  zprintf (int,char*,int,...) ; 

__attribute__((used)) static inline void dump_stats (const zbar_image_scanner_t *iscn)
{
    int i;
    zprintf(1, "symbol sets allocated   = %-4d\n", iscn->stat_syms_new);
    zprintf(1, "    scanner syms in use = %-4d\trecycled  = %-4d\n",
            iscn->stat_iscn_syms_inuse, iscn->stat_iscn_syms_recycle);
    zprintf(1, "    image syms in use   = %-4d\trecycled  = %-4d\n",
            iscn->stat_img_syms_inuse, iscn->stat_img_syms_recycle);
    zprintf(1, "symbols allocated       = %-4d\n", iscn->stat_sym_new);
    for(i = 0; i < RECYCLE_BUCKETS; i++)
        zprintf(1, "     recycled[%d]        = %-4d\n",
                i, iscn->stat_sym_recycle[i]);
}