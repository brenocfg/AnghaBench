#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* ch_size; TYPE_2__** channels; TYPE_1__* avctx; } ;
struct TYPE_10__ {scalar_t__ nb_groups; } ;
struct TYPE_9__ {int err_recognition; } ;
typedef  TYPE_3__ DBEContext ;

/* Variables and functions */
 int AV_EF_EXPLODE ; 
 int convert_input (TYPE_3__*,int,int) ; 
 int parse_channel (TYPE_3__*,int,int) ; 
 int parse_key (TYPE_3__*) ; 
 int skip_input (TYPE_3__*,int) ; 

__attribute__((used)) static int parse_audio(DBEContext *s, int start, int end, int seg_id)
{
    int ch, ret, key;

    if ((key = parse_key(s)) < 0)
        return key;

    for (ch = start; ch < end; ch++) {
        if (!s->ch_size[ch]) {
            s->channels[seg_id][ch].nb_groups = 0;
            continue;
        }
        if ((ret = convert_input(s, s->ch_size[ch], key)) < 0)
            return ret;
        if ((ret = parse_channel(s, ch, seg_id)) < 0) {
            if (s->avctx->err_recognition & AV_EF_EXPLODE)
                return ret;
            s->channels[seg_id][ch].nb_groups = 0;
        }
        if ((ret = skip_input(s, s->ch_size[ch])) < 0)
            return ret;
    }

    return skip_input(s, 1);
}