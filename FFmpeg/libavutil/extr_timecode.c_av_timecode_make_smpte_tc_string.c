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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_TIMECODE_STR_SIZE ; 
 unsigned int bcd2uint (int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,char,unsigned int) ; 

char *av_timecode_make_smpte_tc_string(char *buf, uint32_t tcsmpte, int prevent_df)
{
    unsigned hh   = bcd2uint(tcsmpte     & 0x3f);    // 6-bit hours
    unsigned mm   = bcd2uint(tcsmpte>>8  & 0x7f);    // 7-bit minutes
    unsigned ss   = bcd2uint(tcsmpte>>16 & 0x7f);    // 7-bit seconds
    unsigned ff   = bcd2uint(tcsmpte>>24 & 0x3f);    // 6-bit frames
    unsigned drop = tcsmpte & 1<<30 && !prevent_df;  // 1-bit drop if not arbitrary bit
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    return buf;
}