#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct AVHWFramesContext {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_pool_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvdec_free_dummy(struct AVHWFramesContext *ctx)
{
    av_buffer_pool_uninit(&ctx->pool);
}