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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTE_ApplyPatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  __wpad_patch_finished ; 
 int /*<<< orphan*/  __wpads_ponded ; 

__attribute__((used)) static s32 __readlinkkey_finished(s32 result,void *usrdata)
{
	//printf("__readlinkkey_finished(%d)\n",result);

	__wpads_ponded = result;
	BTE_ApplyPatch(__wpad_patch_finished);

	return ERR_OK;
}