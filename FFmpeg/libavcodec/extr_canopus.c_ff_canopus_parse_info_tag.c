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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_5__ {int /*<<< orphan*/  field_order; TYPE_1__ sample_aspect_ratio; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_FIELD_BB ; 
 int /*<<< orphan*/  AV_FIELD_PROGRESSIVE ; 
 int /*<<< orphan*/  AV_FIELD_TT ; 
 int /*<<< orphan*/  av_reduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 

int ff_canopus_parse_info_tag(AVCodecContext *avctx,
                              const uint8_t *src, size_t size)
{
    GetByteContext gbc;
    int par_x, par_y, field_order;

    bytestream2_init(&gbc, src, size);

    /* Parse aspect ratio. */
    bytestream2_skip(&gbc, 8); // unknown, 16 bits 1
    par_x = bytestream2_get_le32(&gbc);
    par_y = bytestream2_get_le32(&gbc);
    if (par_x && par_y)
        av_reduce(&avctx->sample_aspect_ratio.num,
                  &avctx->sample_aspect_ratio.den,
                  par_x, par_y, 255);

    /* Short INFO tag (used in CLLC) has only AR data. */
    if (size == 0x18)
        return 0;

    bytestream2_skip(&gbc, 16); // unknown RDRT tag

    /* Parse FIEL tag. */
    bytestream2_skip(&gbc, 8); // 'FIEL' and 4 bytes 0
    field_order = bytestream2_get_le32(&gbc);
    switch (field_order) {
    case 0: avctx->field_order = AV_FIELD_TT; break;
    case 1: avctx->field_order = AV_FIELD_BB; break;
    case 2: avctx->field_order = AV_FIELD_PROGRESSIVE; break;
    }

    return 0;
}