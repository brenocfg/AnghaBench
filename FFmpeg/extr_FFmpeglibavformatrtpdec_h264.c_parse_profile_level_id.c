#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_3__ {void* level_idc; void* profile_iop; void* profile_idc; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,void*,void*,void*) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void parse_profile_level_id(AVFormatContext *s,
                                   PayloadContext *h264_data,
                                   const char *value)
{
    char buffer[3];
    // 6 characters=3 bytes, in hex.
    uint8_t profile_idc;
    uint8_t profile_iop;
    uint8_t level_idc;

    buffer[0]   = value[0];
    buffer[1]   = value[1];
    buffer[2]   = '\0';
    profile_idc = strtol(buffer, NULL, 16);
    buffer[0]   = value[2];
    buffer[1]   = value[3];
    profile_iop = strtol(buffer, NULL, 16);
    buffer[0]   = value[4];
    buffer[1]   = value[5];
    level_idc   = strtol(buffer, NULL, 16);

    av_log(s, AV_LOG_DEBUG,
           "RTP Profile IDC: %x Profile IOP: %x Level: %x\n",
           profile_idc, profile_iop, level_idc);
    h264_data->profile_idc = profile_idc;
    h264_data->profile_iop = profile_iop;
    h264_data->level_idc   = level_idc;
}