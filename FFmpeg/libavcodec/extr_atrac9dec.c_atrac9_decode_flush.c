#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* channel; } ;
struct TYPE_10__ {int /*<<< orphan*/  prev_win; } ;
struct TYPE_9__ {TYPE_1__* block_config; TYPE_5__* block; } ;
struct TYPE_8__ {TYPE_3__* priv_data; } ;
struct TYPE_7__ {int count; scalar_t__* type; } ;
typedef  TYPE_2__ AVCodecContext ;
typedef  TYPE_3__ ATRAC9Context ;
typedef  TYPE_4__ ATRAC9ChannelData ;
typedef  TYPE_5__ ATRAC9BlockData ;

/* Variables and functions */
 scalar_t__ ATRAC9_BLOCK_TYPE_CPE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atrac9_decode_flush(AVCodecContext *avctx)
{
    ATRAC9Context *s = avctx->priv_data;

    for (int j = 0; j < s->block_config->count; j++) {
        ATRAC9BlockData *b = &s->block[j];
        const int stereo = s->block_config->type[j] == ATRAC9_BLOCK_TYPE_CPE;
        for (int i = 0; i <= stereo; i++) {
            ATRAC9ChannelData *c = &b->channel[i];
            memset(c->prev_win, 0, sizeof(c->prev_win));
        }
    }
}