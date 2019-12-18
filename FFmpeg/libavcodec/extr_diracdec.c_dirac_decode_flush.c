#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int frame_number; scalar_t__ seen_sequence_header; } ;
typedef  TYPE_1__ DiracContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  free_sequence_buffers (TYPE_1__*) ; 

__attribute__((used)) static void dirac_decode_flush(AVCodecContext *avctx)
{
    DiracContext *s = avctx->priv_data;
    free_sequence_buffers(s);
    s->seen_sequence_header = 0;
    s->frame_number = -1;
}