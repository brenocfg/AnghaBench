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
typedef  enum dv_pack_type { ____Placeholder_dv_pack_type } dv_pack_type ;

/* Variables and functions */
#define  dv_audio_control 131 
#define  dv_audio_source 130 
#define  dv_timecode 129 
#define  dv_video_control 128 

__attribute__((used)) static const uint8_t *dv_extract_pack(const uint8_t *frame, enum dv_pack_type t)
{
    int offs;
    int c;

    for (c = 0; c < 10; c++) {
        switch (t) {
        case dv_audio_source:
            if (c&1)    offs = (80 * 6 + 80 * 16 * 0 + 3 + c*12000);
            else        offs = (80 * 6 + 80 * 16 * 3 + 3 + c*12000);
            break;
        case dv_audio_control:
            if (c&1)    offs = (80 * 6 + 80 * 16 * 1 + 3 + c*12000);
            else        offs = (80 * 6 + 80 * 16 * 4 + 3 + c*12000);
            break;
        case dv_video_control:
            if (c&1)    offs = (80 * 3 + 8      + c*12000);
            else        offs = (80 * 5 + 48 + 5 + c*12000);
            break;
        case dv_timecode:
            offs = (80*1 + 3 + 3);
            break;
        default:
            return NULL;
        }
        if (frame[offs] == t)
            break;
    }

    return frame[offs] == t ? &frame[offs] : NULL;
}