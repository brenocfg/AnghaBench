#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVPacketSideDataType { ____Placeholder_AVPacketSideDataType } AVPacketSideDataType ;
struct TYPE_5__ {int nb_side_data; TYPE_1__* side_data; } ;
struct TYPE_4__ {int type; int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVStream ;

/* Variables and functions */

uint8_t *av_stream_get_side_data(const AVStream *st,
                                 enum AVPacketSideDataType type, int *size)
{
    int i;

    for (i = 0; i < st->nb_side_data; i++) {
        if (st->side_data[i].type == type) {
            if (size)
                *size = st->side_data[i].size;
            return st->side_data[i].data;
        }
    }
    return NULL;
}