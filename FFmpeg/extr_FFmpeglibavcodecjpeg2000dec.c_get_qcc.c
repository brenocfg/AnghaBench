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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int ncomponents; int /*<<< orphan*/  avctx; int /*<<< orphan*/  g; } ;
typedef  int /*<<< orphan*/  Jpeg2000QuantStyle ;
typedef  TYPE_1__ Jpeg2000DecoderContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  HAD_QCC ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int get_qcx (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_qcc(Jpeg2000DecoderContext *s, int n, Jpeg2000QuantStyle *q,
                   uint8_t *properties)
{
    int compno;

    if (bytestream2_get_bytes_left(&s->g) < 1)
        return AVERROR_INVALIDDATA;

    compno = bytestream2_get_byteu(&s->g);

    if (compno >= s->ncomponents) {
        av_log(s->avctx, AV_LOG_ERROR,
               "Invalid compno %d. There are %d components in the image.\n",
               compno, s->ncomponents);
        return AVERROR_INVALIDDATA;
    }

    properties[compno] |= HAD_QCC;
    return get_qcx(s, n - 1, q + compno);
}