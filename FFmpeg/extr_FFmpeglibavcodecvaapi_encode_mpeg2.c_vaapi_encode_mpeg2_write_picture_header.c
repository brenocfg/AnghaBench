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
typedef  int /*<<< orphan*/  VAAPIEncodePicture ;
struct TYPE_6__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/  picture_coding_extension; int /*<<< orphan*/  picture_header; int /*<<< orphan*/  current_fragment; } ;
typedef  TYPE_1__ VAAPIEncodeMPEG2Context ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  CodedBitstreamFragment ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  MPEG2_START_EXTENSION ; 
 int /*<<< orphan*/  MPEG2_START_PICTURE ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vaapi_encode_mpeg2_add_header (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vaapi_encode_mpeg2_write_fragment (TYPE_2__*,char*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vaapi_encode_mpeg2_write_picture_header(AVCodecContext *avctx,
                                                   VAAPIEncodePicture *pic,
                                                   char *data, size_t *data_len)
{
    VAAPIEncodeMPEG2Context *priv = avctx->priv_data;
    CodedBitstreamFragment  *frag = &priv->current_fragment;
    int err;

    err = vaapi_encode_mpeg2_add_header(avctx, frag, MPEG2_START_PICTURE,
                                        &priv->picture_header);
    if (err < 0)
        goto fail;

    err = vaapi_encode_mpeg2_add_header(avctx, frag, MPEG2_START_EXTENSION,
                                        &priv->picture_coding_extension);
    if (err < 0)
        goto fail;

    err = vaapi_encode_mpeg2_write_fragment(avctx, data, data_len, frag);
fail:
    ff_cbs_fragment_reset(priv->cbc, frag);
    return 0;
}