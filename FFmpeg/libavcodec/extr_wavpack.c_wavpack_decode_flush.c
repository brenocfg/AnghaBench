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
struct TYPE_4__ {int fdec_num; int /*<<< orphan*/ * fdec; } ;
typedef  TYPE_1__ WavpackContext ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  wv_reset_saved_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wavpack_decode_flush(AVCodecContext *avctx)
{
    WavpackContext *s = avctx->priv_data;
    int i;

    for (i = 0; i < s->fdec_num; i++)
        wv_reset_saved_context(s->fdec[i]);
}