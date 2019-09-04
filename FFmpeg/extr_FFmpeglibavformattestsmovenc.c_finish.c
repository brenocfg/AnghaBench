#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pb; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_write_trailer (TYPE_1__*) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_context_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* ctx ; 

__attribute__((used)) static void finish(void)
{
    av_write_trailer(ctx);
    avio_context_free(&ctx->pb);
    avformat_free_context(ctx);
    ctx = NULL;
}