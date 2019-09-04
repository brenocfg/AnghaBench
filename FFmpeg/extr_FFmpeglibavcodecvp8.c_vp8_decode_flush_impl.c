#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  framep; int /*<<< orphan*/ * frames; } ;
typedef  TYPE_1__ VP8Context ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_buffers (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vp8_release_frame (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vp8_decode_flush_impl(AVCodecContext *avctx, int free_mem)
{
    VP8Context *s = avctx->priv_data;
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(s->frames); i++)
        vp8_release_frame(s, &s->frames[i]);
    memset(s->framep, 0, sizeof(s->framep));

    if (free_mem)
        free_buffers(s);
}