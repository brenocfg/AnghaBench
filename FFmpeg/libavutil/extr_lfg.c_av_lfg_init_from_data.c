#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {unsigned int* state; scalar_t__ index; } ;
typedef  TYPE_1__ AVLFG ;
typedef  int /*<<< orphan*/  AVCRC ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CRC_32_IEEE ; 
 int /*<<< orphan*/  EINVAL ; 
 unsigned int UINT_MAX ; 
 int av_crc (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/ * av_crc_get_table (int /*<<< orphan*/ ) ; 

int av_lfg_init_from_data(AVLFG *c, const uint8_t *data, unsigned int length) {
    unsigned int beg, end, segm;
    const AVCRC *avcrc;
    uint32_t crc = 1;

    /* avoid integer overflow in the loop below. */
    if (length > (UINT_MAX / 128U)) return AVERROR(EINVAL);

    c->index = 0;
    avcrc = av_crc_get_table(AV_CRC_32_IEEE); /* This can't fail. It's a well-defined table in crc.c */

    /* across 64 segments of the incoming data,
     * do a running crc of each segment and store the crc as the state for that slot.
     * this works even if the length of the segment is 0 bytes. */
    beg = 0;
    for (segm = 0;segm < 64;segm++) {
        end = (((segm + 1) * length) / 64);
        crc = av_crc(avcrc, crc, data + beg, end - beg);
        c->state[segm] = (unsigned int)crc;
        beg = end;
    }

    return 0;
}