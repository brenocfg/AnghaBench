#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  DCACoreFrameHeader ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ ff_dca_parse_core_frame_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int avpriv_dca_parse_core_frame_header(DCACoreFrameHeader *h, const uint8_t *buf, int size)
{
    GetBitContext gb;
    int ret;

    ret = init_get_bits8(&gb, buf, size);
    if (ret < 0)
        return ret;

    if (ff_dca_parse_core_frame_header(h, &gb) < 0)
        return AVERROR_INVALIDDATA;

    return 0;
}