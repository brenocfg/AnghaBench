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
typedef  int /*<<< orphan*/  MPEG4AudioConfig ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int ff_mpeg4audio_get_config_gb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int avpriv_mpeg4audio_get_config(MPEG4AudioConfig *c, const uint8_t *buf,
                                 int bit_size, int sync_extension)
{
    GetBitContext gb;
    int ret;

    if (bit_size <= 0)
        return AVERROR_INVALIDDATA;

    ret = init_get_bits(&gb, buf, bit_size);
    if (ret < 0)
        return ret;

    return ff_mpeg4audio_get_config_gb(c, &gb, sync_extension, NULL);
}