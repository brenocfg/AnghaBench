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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int av_dict_set (int /*<<< orphan*/ **,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,char,int) ; 

__attribute__((used)) static int add_timecode_metadata(AVDictionary **pm, const char *key, uint32_t timecode, int fields_per_frame)
{
   char tmp[128];
   int field  = timecode & 0xff;
   int frame  = fields_per_frame ? field / fields_per_frame : field;
   int second = (timecode >>  8) & 0xff;
   int minute = (timecode >> 16) & 0xff;
   int hour   = (timecode >> 24) & 0x1f;
   int drop   = (timecode >> 29) & 1;
   // bit 30: color_frame, unused
   // ignore invalid time code
   if (timecode >> 31)
       return 0;
   snprintf(tmp, sizeof(tmp), "%02d:%02d:%02d%c%02d",
       hour, minute, second, drop ? ';' : ':', frame);
   return av_dict_set(pm, key, tmp, 0);
}