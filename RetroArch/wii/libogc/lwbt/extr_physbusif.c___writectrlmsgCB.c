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
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ctrlbufs ; 

__attribute__((used)) static s32 __writectrlmsgCB(s32 result,void *usrdata)
{
	if(usrdata!=NULL) btmemb_free(&ctrlbufs,usrdata);
	return result;
}