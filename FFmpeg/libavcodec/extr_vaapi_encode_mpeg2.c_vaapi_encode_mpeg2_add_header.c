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
struct TYPE_5__ {int /*<<< orphan*/  cbc; } ;
typedef  TYPE_1__ VAAPIEncodeMPEG2Context ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  CodedBitstreamFragment ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int ff_cbs_insert_unit_content (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vaapi_encode_mpeg2_add_header(AVCodecContext *avctx,
                                         CodedBitstreamFragment *frag,
                                         int type, void *header)
{
    VAAPIEncodeMPEG2Context *priv = avctx->priv_data;
    int err;

    err = ff_cbs_insert_unit_content(priv->cbc, frag, -1, type, header, NULL);
    if (err < 0) {
        av_log(avctx, AV_LOG_ERROR, "Failed to add header: "
               "type = %d.\n", type);
        return err;
    }

    return 0;
}