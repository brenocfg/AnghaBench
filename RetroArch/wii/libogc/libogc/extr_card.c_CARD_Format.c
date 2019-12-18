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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_GetFontEncoding () ; 
 int /*<<< orphan*/  __card_formatregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_synccallback ; 

s32 CARD_Format(s32 chn)
{
	s32 ret;
	u32 enc;

	enc = SYS_GetFontEncoding();
	if((ret=__card_formatregion(chn,enc,__card_synccallback))>=0) {
		ret = __card_sync(chn);
	}
	return ret;
}