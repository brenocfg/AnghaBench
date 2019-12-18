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
struct VideoModeTable {int ModeIndex; } ;

/* Variables and functions */
 struct VideoModeTable* CEA_HDMI_Modes ; 
 struct VideoModeTable* CLE266Modes ; 
 int NUM_TOTAL_CEA_MODES ; 
 int NUM_TOTAL_MODETABLE ; 

struct VideoModeTable *viafb_get_cea_mode_tbl_pointer(int Index)
{
	struct VideoModeTable *TmpTbl = NULL;
	int i = 0;
	while ((i < NUM_TOTAL_CEA_MODES) &&
			(Index != CEA_HDMI_Modes[i].ModeIndex))
		i++;
	if ((i < NUM_TOTAL_CEA_MODES))
		TmpTbl = &CEA_HDMI_Modes[i];
	 else {
		/*Still use general timing if don't find CEA timing */
		i = 0;
		while ((i < NUM_TOTAL_MODETABLE) &&
				(Index != CLE266Modes[i].ModeIndex))
		       i++;
		if (i >= NUM_TOTAL_MODETABLE)
			i = 0;
		TmpTbl = &CLE266Modes[i];
	}
	return TmpTbl;
}