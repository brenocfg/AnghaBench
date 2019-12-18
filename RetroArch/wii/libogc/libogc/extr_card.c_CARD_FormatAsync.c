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
typedef  int /*<<< orphan*/  cardcallback ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_GetFontEncoding () ; 
 int /*<<< orphan*/  __card_formatregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 CARD_FormatAsync(s32 chn,cardcallback callback)
{
	u32 enc;

	enc = SYS_GetFontEncoding();
	return __card_formatregion(chn,enc,callback);
}