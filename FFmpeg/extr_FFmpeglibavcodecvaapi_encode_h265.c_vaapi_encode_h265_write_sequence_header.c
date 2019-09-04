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
struct TYPE_6__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/  raw_pps; int /*<<< orphan*/  raw_sps; int /*<<< orphan*/  raw_vps; scalar_t__ aud_needed; int /*<<< orphan*/  raw_aud; int /*<<< orphan*/  current_access_unit; } ;
typedef  TYPE_1__ VAAPIEncodeH265Context ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  CodedBitstreamFragment ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vaapi_encode_h265_add_nal (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vaapi_encode_h265_write_access_unit (TYPE_2__*,char*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vaapi_encode_h265_write_sequence_header(AVCodecContext *avctx,
                                                   char *data, size_t *data_len)
{
    VAAPIEncodeH265Context *priv = avctx->priv_data;
    CodedBitstreamFragment   *au = &priv->current_access_unit;
    int err;

    if (priv->aud_needed) {
        err = vaapi_encode_h265_add_nal(avctx, au, &priv->raw_aud);
        if (err < 0)
            goto fail;
        priv->aud_needed = 0;
    }

    err = vaapi_encode_h265_add_nal(avctx, au, &priv->raw_vps);
    if (err < 0)
        goto fail;

    err = vaapi_encode_h265_add_nal(avctx, au, &priv->raw_sps);
    if (err < 0)
        goto fail;

    err = vaapi_encode_h265_add_nal(avctx, au, &priv->raw_pps);
    if (err < 0)
        goto fail;

    err = vaapi_encode_h265_write_access_unit(avctx, data, data_len, au);
fail:
    ff_cbs_fragment_reset(priv->cbc, au);
    return err;
}