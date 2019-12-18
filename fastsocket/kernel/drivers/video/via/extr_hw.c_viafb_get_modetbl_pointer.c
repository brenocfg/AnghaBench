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
struct VideoModeTable {int dummy; } ;

/* Variables and functions */
 struct VideoModeTable* CLE266Modes ; 
 size_t search_mode_setting (int) ; 

struct VideoModeTable *viafb_get_modetbl_pointer(int Index)
{
	struct VideoModeTable *TmpTbl = NULL;
	TmpTbl = &CLE266Modes[search_mode_setting(Index)];
	return TmpTbl;
}