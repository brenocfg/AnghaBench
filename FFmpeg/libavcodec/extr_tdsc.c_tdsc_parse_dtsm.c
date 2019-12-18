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
struct TYPE_7__ {int err_recognition; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  gbc; void* cursor_y; void* cursor_x; } ;
typedef  TYPE_1__ TDSCContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_2__*,char*,int) ; 
 void* bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int tdsc_load_cursor (TYPE_2__*) ; 

__attribute__((used)) static int tdsc_parse_dtsm(AVCodecContext *avctx)
{
    TDSCContext *ctx = avctx->priv_data;
    int ret;
    int action = bytestream2_get_le32(&ctx->gbc);

    bytestream2_skip(&ctx->gbc, 4); // some kind of ID or version maybe?

    if (action == 2 || action == 3) {
        /* Load cursor coordinates */
        ctx->cursor_x = bytestream2_get_le32(&ctx->gbc);
        ctx->cursor_y = bytestream2_get_le32(&ctx->gbc);

        /* Load a full cursor sprite */
        if (action == 3) {
            ret = tdsc_load_cursor(avctx);
            /* Do not consider cursor errors fatal unless in explode mode */
            if (ret < 0 && (avctx->err_recognition & AV_EF_EXPLODE))
                return ret;
        }
    } else {
        avpriv_request_sample(avctx, "Cursor action %d", action);
    }

    return 0;
}