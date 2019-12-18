#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct bd_addr {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {size_t num_registered; TYPE_1__* registered; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR (struct bd_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  WPAD_STATE_ENABLED ; 
 int /*<<< orphan*/  __wpad_assign_slot ; 
 TYPE_2__ __wpad_devs ; 
 int /*<<< orphan*/  __wpads_inited ; 
 int /*<<< orphan*/ * __wpads_listen ; 
 int /*<<< orphan*/  wiiuse_register (int /*<<< orphan*/ *,struct bd_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 __wpad_init_finished(s32 result,void *usrdata)
{
	u32 i;
	struct bd_addr bdaddr;

	//printf("__wpad_init_finished(%d)\n",result);

   if(result==ERR_OK) {
      for(i=0;/*__wpads[i] && */i<__wpad_devs.num_registered;i++) {
         BD_ADDR(&(bdaddr),__wpad_devs.registered[i].bdaddr[5],__wpad_devs.registered[i].bdaddr[4],__wpad_devs.registered[i].bdaddr[3],__wpad_devs.registered[i].bdaddr[2],__wpad_devs.registered[i].bdaddr[1],__wpad_devs.registered[i].bdaddr[0]);
         wiiuse_register(&__wpads_listen[i],&(bdaddr),__wpad_assign_slot);
      }
   }
   __wpads_inited = WPAD_STATE_ENABLED;
	return ERR_OK;
}