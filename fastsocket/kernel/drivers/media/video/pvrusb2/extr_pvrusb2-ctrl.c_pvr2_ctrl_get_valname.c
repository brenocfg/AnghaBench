#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pvr2_ctrl {TYPE_5__* hdw; TYPE_4__* info; } ;
struct TYPE_10__ {int /*<<< orphan*/  big_lock; } ;
struct TYPE_7__ {char** bit_names; int valid_bits; } ;
struct TYPE_6__ {char** value_names; } ;
struct TYPE_8__ {TYPE_2__ type_bitmask; TYPE_1__ type_enum; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_3__ def; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 scalar_t__ pvr2_ctl_bitmask ; 
 scalar_t__ pvr2_ctl_enum ; 
 scalar_t__ pvr2_ctrl_range_check (struct pvr2_ctrl*,int) ; 
 unsigned int scnprintf (char*,unsigned int,char*,char const*) ; 

int pvr2_ctrl_get_valname(struct pvr2_ctrl *cptr,int val,
			  char *bptr,unsigned int bmax,
			  unsigned int *blen)
{
	int ret = -EINVAL;
	if (!cptr) return 0;
	*blen = 0;
	LOCK_TAKE(cptr->hdw->big_lock); do {
		if (cptr->info->type == pvr2_ctl_enum) {
			const char * const *names;
			names = cptr->info->def.type_enum.value_names;
			if (pvr2_ctrl_range_check(cptr,val) == 0) {
				if (names[val]) {
					*blen = scnprintf(
						bptr,bmax,"%s",
						names[val]);
				} else {
					*blen = 0;
				}
				ret = 0;
			}
		} else if (cptr->info->type == pvr2_ctl_bitmask) {
			const char **names;
			unsigned int idx;
			int msk;
			names = cptr->info->def.type_bitmask.bit_names;
			val &= cptr->info->def.type_bitmask.valid_bits;
			for (idx = 0, msk = 1; val; idx++, msk <<= 1) {
				if (val & msk) {
					*blen = scnprintf(bptr,bmax,"%s",
							  names[idx]);
					ret = 0;
					break;
				}
			}
		}
	} while(0); LOCK_GIVE(cptr->hdw->big_lock);
	return ret;
}