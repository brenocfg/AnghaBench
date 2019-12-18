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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  num_aac_frames; int /*<<< orphan*/  samples; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AACADTSHeaderInfo ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_AAC_ADTS_HEADER_SIZE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int ff_adts_header_parse (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int av_adts_header_parse(const uint8_t *buf, uint32_t *samples, uint8_t *frames)
{
#if CONFIG_ADTS_HEADER
    GetBitContext gb;
    AACADTSHeaderInfo hdr;
    int err = init_get_bits8(&gb, buf, AV_AAC_ADTS_HEADER_SIZE);
    if (err < 0)
        return err;
    err = ff_adts_header_parse(&gb, &hdr);
    if (err < 0)
        return err;
    *samples = hdr.samples;
    *frames  = hdr.num_aac_frames;
    return 0;
#else
    return AVERROR(ENOSYS);
#endif
}