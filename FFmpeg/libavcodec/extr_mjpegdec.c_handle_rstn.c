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
struct TYPE_5__ {scalar_t__ restart_count; int* last_dc; int bits; int /*<<< orphan*/  gb; TYPE_1__* avctx; scalar_t__ restart_interval; } ;
struct TYPE_4__ {scalar_t__ codec_id; } ;
typedef  TYPE_2__ MJpegDecodeContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_THP ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int handle_rstn(MJpegDecodeContext *s, int nb_components)
{
    int i;
    int reset = 0;

    if (s->restart_interval) {
        s->restart_count--;
        if(s->restart_count == 0 && s->avctx->codec_id == AV_CODEC_ID_THP){
            align_get_bits(&s->gb);
            for (i = 0; i < nb_components; i++) /* reset dc */
                s->last_dc[i] = (4 << s->bits);
        }

        i = 8 + ((-get_bits_count(&s->gb)) & 7);
        /* skip RSTn */
        if (s->restart_count == 0) {
            if(   show_bits(&s->gb, i) == (1 << i) - 1
               || show_bits(&s->gb, i) == 0xFF) {
                int pos = get_bits_count(&s->gb);
                align_get_bits(&s->gb);
                while (get_bits_left(&s->gb) >= 8 && show_bits(&s->gb, 8) == 0xFF)
                    skip_bits(&s->gb, 8);
                if (get_bits_left(&s->gb) >= 8 && (get_bits(&s->gb, 8) & 0xF8) == 0xD0) {
                    for (i = 0; i < nb_components; i++) /* reset dc */
                        s->last_dc[i] = (4 << s->bits);
                    reset = 1;
                } else
                    skip_bits_long(&s->gb, pos - get_bits_count(&s->gb));
            }
        }
    }
    return reset;
}