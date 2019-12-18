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
typedef  int /*<<< orphan*/  card_dir ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DeleteEntryAsync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_synccallback ; 

s32 CARD_DeleteEntry(s32 chn,card_dir *dir_entry)
{
	s32 ret;
	if((ret=CARD_DeleteEntryAsync(chn,dir_entry,__card_synccallback))>=0) {
		ret = __card_sync(chn);
	}
	return ret;
}