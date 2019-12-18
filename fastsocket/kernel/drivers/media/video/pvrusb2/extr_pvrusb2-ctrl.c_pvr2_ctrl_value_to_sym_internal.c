#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pvr2_ctrl {TYPE_4__* info; } ;
struct TYPE_6__ {int valid_bits; int /*<<< orphan*/  bit_names; } ;
struct TYPE_5__ {char** value_names; int count; } ;
struct TYPE_7__ {TYPE_2__ type_bitmask; TYPE_1__ type_enum; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_3__ def; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int gen_bitmask_string (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ pvr2_ctl_bitmask ; 
 scalar_t__ pvr2_ctl_bool ; 
 scalar_t__ pvr2_ctl_enum ; 
 scalar_t__ pvr2_ctl_int ; 
 unsigned int scnprintf (char*,unsigned int,char*,...) ; 

int pvr2_ctrl_value_to_sym_internal(struct pvr2_ctrl *cptr,
				    int mask,int val,
				    char *buf,unsigned int maxlen,
				    unsigned int *len)
{
	int ret = -EINVAL;

	*len = 0;
	if (cptr->info->type == pvr2_ctl_int) {
		*len = scnprintf(buf,maxlen,"%d",val);
		ret = 0;
	} else if (cptr->info->type == pvr2_ctl_bool) {
		*len = scnprintf(buf,maxlen,"%s",val ? "true" : "false");
		ret = 0;
	} else if (cptr->info->type == pvr2_ctl_enum) {
		const char * const *names;
		names = cptr->info->def.type_enum.value_names;
		if ((val >= 0) &&
		    (val < cptr->info->def.type_enum.count)) {
			if (names[val]) {
				*len = scnprintf(
					buf,maxlen,"%s",
					names[val]);
			} else {
				*len = 0;
			}
			ret = 0;
		}
	} else if (cptr->info->type == pvr2_ctl_bitmask) {
		*len = gen_bitmask_string(
			val & mask & cptr->info->def.type_bitmask.valid_bits,
			~0,!0,
			cptr->info->def.type_bitmask.bit_names,
			buf,maxlen);
	}
	return ret;
}