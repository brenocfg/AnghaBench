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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTE_ReadStoredLinkKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  WPAD_MAX_WIIMOTES ; 
 int /*<<< orphan*/  __readlinkkey_finished ; 
 int /*<<< orphan*/  __wpad_keys ; 

__attribute__((used)) static s32 __initcore_finished(s32 result,void *usrdata)
{
	//printf("__initcore_finished(%d)\n",result);

	if(result==ERR_OK) {
		BTE_ReadStoredLinkKey(__wpad_keys,WPAD_MAX_WIIMOTES,__readlinkkey_finished);
	}
	return ERR_OK;
}