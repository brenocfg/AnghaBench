#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cbc; } ;
typedef  TYPE_1__ VAAPIEncodeH265Context ;
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {int data_size; int data_bit_padding; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ CodedBitstreamFragment ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_cbs_write_fragment_data (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vaapi_encode_h265_write_access_unit(AVCodecContext *avctx,
                                               char *data, size_t *data_len,
                                               CodedBitstreamFragment *au)
{
    VAAPIEncodeH265Context *priv = avctx->priv_data;
    int err;

    err = ff_cbs_write_fragment_data(priv->cbc, au);
    if (err < 0) {
        av_log(avctx, AV_LOG_ERROR, "Failed to write packed header.\n");
        return err;
    }

    if (*data_len < 8 * au->data_size - au->data_bit_padding) {
        av_log(avctx, AV_LOG_ERROR, "Access unit too large: "
               "%zu < %zu.\n", *data_len,
               8 * au->data_size - au->data_bit_padding);
        return AVERROR(ENOSPC);
    }

    memcpy(data, au->data, au->data_size);
    *data_len = 8 * au->data_size - au->data_bit_padding;

    return 0;
}