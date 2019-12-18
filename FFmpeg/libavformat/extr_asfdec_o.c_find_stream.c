#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {int nb_streams; TYPE_1__** asf_st; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** streams; TYPE_3__* priv_data; } ;
struct TYPE_5__ {scalar_t__ stream_index; size_t index; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASFContext ;

/* Variables and functions */

__attribute__((used)) static AVStream *find_stream(AVFormatContext *s, uint16_t st_num)
{
    AVStream *st = NULL;
    ASFContext *asf = s->priv_data;
    int i;

    for (i = 0; i < asf->nb_streams; i++) {
        if (asf->asf_st[i]->stream_index == st_num) {
            st = s->streams[asf->asf_st[i]->index];
            break;
        }
    }

    return st;
}