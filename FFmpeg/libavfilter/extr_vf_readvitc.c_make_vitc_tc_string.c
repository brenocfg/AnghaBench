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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_TIMECODE_STR_SIZE ; 
 unsigned int bcd2uint (int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,char,unsigned int) ; 

__attribute__((used)) static char *make_vitc_tc_string(char *buf, uint8_t *line)
{
    unsigned hh   = bcd2uint(line[7] & 0x03, line[6] & 0x0f);  // 6-bit hours
    unsigned mm   = bcd2uint(line[5] & 0x07, line[4] & 0x0f);  // 7-bit minutes
    unsigned ss   = bcd2uint(line[3] & 0x07, line[2] & 0x0f);  // 7-bit seconds
    unsigned ff   = bcd2uint(line[1] & 0x03, line[0] & 0x0f);  // 6-bit frames
    unsigned drop = (line[1] & 0x04);                          // 1-bit drop flag
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    return buf;
}