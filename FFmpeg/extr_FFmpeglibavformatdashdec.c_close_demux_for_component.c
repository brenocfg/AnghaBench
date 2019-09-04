#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
struct representation {TYPE_2__* ctx; TYPE_1__ pb; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_2__**) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

__attribute__((used)) static void close_demux_for_component(struct representation *pls)
{
    /* note: the internal buffer could have changed */
    av_freep(&pls->pb.buffer);
    memset(&pls->pb, 0x00, sizeof(AVIOContext));
    pls->ctx->pb = NULL;
    avformat_close_input(&pls->ctx);
    pls->ctx = NULL;
}