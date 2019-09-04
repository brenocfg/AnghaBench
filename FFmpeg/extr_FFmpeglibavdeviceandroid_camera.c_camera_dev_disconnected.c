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
struct TYPE_4__ {int /*<<< orphan*/  exit; } ;
typedef  TYPE_1__ AndroidCameraCtx ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  ACameraDevice ;

/* Variables and functions */
 int /*<<< orphan*/  ACameraDevice_getId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void camera_dev_disconnected(void *context, ACameraDevice *device)
{
    AVFormatContext *avctx = context;
    AndroidCameraCtx *ctx = avctx->priv_data;
    atomic_store(&ctx->exit, 1);
    av_log(avctx, AV_LOG_ERROR, "Camera with id %s disconnected.\n",
           ACameraDevice_getId(device));
}