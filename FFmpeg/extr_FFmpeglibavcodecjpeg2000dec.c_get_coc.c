#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {void* csty; } ;
struct TYPE_7__ {int ncomponents; int /*<<< orphan*/  g; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ Jpeg2000DecoderContext ;
typedef  TYPE_2__ Jpeg2000CodingStyle ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  HAD_COC ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int get_cox (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int get_coc(Jpeg2000DecoderContext *s, Jpeg2000CodingStyle *c,
                   uint8_t *properties)
{
    int compno, ret;

    if (bytestream2_get_bytes_left(&s->g) < 2) {
        av_log(s->avctx, AV_LOG_ERROR, "Insufficient space for COC\n");
        return AVERROR_INVALIDDATA;
    }

    compno = bytestream2_get_byteu(&s->g);

    if (compno >= s->ncomponents) {
        av_log(s->avctx, AV_LOG_ERROR,
               "Invalid compno %d. There are %d components in the image.\n",
               compno, s->ncomponents);
        return AVERROR_INVALIDDATA;
    }

    c      += compno;
    c->csty = bytestream2_get_byteu(&s->g);

    if ((ret = get_cox(s, c)) < 0)
        return ret;

    properties[compno] |= HAD_COC;
    return 0;
}