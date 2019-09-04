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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__ got_keyframe; } ;
typedef  TYPE_1__ AVSContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */

__attribute__((used)) static void cavs_flush(AVCodecContext * avctx)
{
    AVSContext *h = avctx->priv_data;
    h->got_keyframe = 0;
}