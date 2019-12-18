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
typedef  size_t u32 ;
struct TYPE_3__ {size_t max_id; int /*<<< orphan*/ ** local_table; } ;
typedef  TYPE_1__ lwp_objinfo ;
typedef  int /*<<< orphan*/  lwp_obj ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (size_t) ; 

lwp_obj* __lwp_objmgr_getisrdisable(lwp_objinfo *info,u32 id,u32 *p_level)
{
	u32 level;
	lwp_obj *object = NULL;

	_CPU_ISR_Disable(level);
	if(info->max_id>=id) {
		if((object=info->local_table[id])!=NULL) {
			*p_level = level;
			return object;
		}
	}
	_CPU_ISR_Restore(level);
	return NULL;
}