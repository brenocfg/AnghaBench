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
struct TYPE_5__ {int /*<<< orphan*/  frame2; int /*<<< orphan*/  frame1; } ;
typedef  TYPE_1__ RASCContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  clear_plane (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_flush(AVCodecContext *avctx)
{
    RASCContext *s = avctx->priv_data;

    clear_plane(avctx, s->frame1);
    clear_plane(avctx, s->frame2);
}