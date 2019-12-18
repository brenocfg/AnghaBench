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
struct TYPE_3__ {int sort; size_t low; int high; int x; } ;
typedef  TYPE_1__ vorbis_floor1_entry ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int ff_vorbis_ready_floor1_list(AVCodecContext *avctx,
                                vorbis_floor1_entry *list, int values)
{
    int i;
    list[0].sort = 0;
    list[1].sort = 1;
    for (i = 2; i < values; i++) {
        int j;
        list[i].low  = 0;
        list[i].high = 1;
        list[i].sort = i;
        for (j = 2; j < i; j++) {
            int tmp = list[j].x;
            if (tmp < list[i].x) {
                if (tmp > list[list[i].low].x)
                    list[i].low  =  j;
            } else {
                if (tmp < list[list[i].high].x)
                    list[i].high = j;
            }
        }
    }
    for (i = 0; i < values - 1; i++) {
        int j;
        for (j = i + 1; j < values; j++) {
            if (list[i].x == list[j].x) {
                av_log(avctx, AV_LOG_ERROR,
                       "Duplicate value found in floor 1 X coordinates\n");
                return AVERROR_INVALIDDATA;
            }
            if (list[list[i].sort].x > list[list[j].sort].x) {
                int tmp = list[i].sort;
                list[i].sort = list[j].sort;
                list[j].sort = tmp;
            }
        }
    }
    return 0;
}