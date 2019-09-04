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
struct TYPE_3__ {int channel_mode; int /*<<< orphan*/ * delay; } ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
#define  AC3_CHMODE_2F1R 134 
#define  AC3_CHMODE_2F2R 133 
#define  AC3_CHMODE_3F 132 
#define  AC3_CHMODE_3F1R 131 
#define  AC3_CHMODE_3F2R 130 
#define  AC3_CHMODE_DUALMONO 129 
#define  AC3_CHMODE_STEREO 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ac3_upmix_delay(AC3DecodeContext *s)
{
    int channel_data_size = sizeof(s->delay[0]);
    switch (s->channel_mode) {
    case AC3_CHMODE_DUALMONO:
    case AC3_CHMODE_STEREO:
        /* upmix mono to stereo */
        memcpy(s->delay[1], s->delay[0], channel_data_size);
        break;
    case AC3_CHMODE_2F2R:
        memset(s->delay[3], 0, channel_data_size);
    case AC3_CHMODE_2F1R:
        memset(s->delay[2], 0, channel_data_size);
        break;
    case AC3_CHMODE_3F2R:
        memset(s->delay[4], 0, channel_data_size);
    case AC3_CHMODE_3F1R:
        memset(s->delay[3], 0, channel_data_size);
    case AC3_CHMODE_3F:
        memcpy(s->delay[2], s->delay[1], channel_data_size);
        memset(s->delay[1], 0, channel_data_size);
        break;
    }
}