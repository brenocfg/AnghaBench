#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cbc; } ;
typedef  TYPE_1__ VAAPIEncodeH265Context ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  nal_unit_type; } ;
typedef  TYPE_2__ H265RawNALUnitHeader ;
typedef  int /*<<< orphan*/  CodedBitstreamFragment ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ff_cbs_insert_unit_content (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vaapi_encode_h265_add_nal(AVCodecContext *avctx,
                                     CodedBitstreamFragment *au,
                                     void *nal_unit)
{
    VAAPIEncodeH265Context *priv = avctx->priv_data;
    H265RawNALUnitHeader *header = nal_unit;
    int err;

    err = ff_cbs_insert_unit_content(priv->cbc, au, -1,
                                     header->nal_unit_type, nal_unit, NULL);
    if (err < 0) {
        av_log(avctx, AV_LOG_ERROR, "Failed to add NAL unit: "
               "type = %d.\n", header->nal_unit_type);
        return err;
    }

    return 0;
}