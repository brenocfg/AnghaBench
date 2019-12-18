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
typedef  int /*<<< orphan*/  u8 ;
struct card_direntry {int /*<<< orphan*/  permission; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  cardcallback ;

/* Variables and functions */
 int /*<<< orphan*/  __card_getstatusex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct card_direntry*) ; 
 int /*<<< orphan*/  __card_setstatusexasync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct card_direntry*,int /*<<< orphan*/ ) ; 

s32 CARD_SetAttributesAsync(s32 chn,s32 fileno,u8 attr,cardcallback callback)
{
	s32 ret;
	struct card_direntry entry;

	if((ret=__card_getstatusex(chn,fileno,&entry))>=0) {
		entry.permission = attr;
		ret = __card_setstatusexasync(chn,fileno,&entry,callback);
	}
	return ret;
}