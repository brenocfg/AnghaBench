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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline int dv_get_audio_sample_count(const uint8_t *buffer, int dsf)
{
    int samples = buffer[0] & 0x3f; /* samples in this frame - min samples */

    switch ((buffer[3] >> 3) & 0x07) {
    case 0:
        return samples + (dsf ? 1896 : 1580);
    case 1:
        return samples + (dsf ? 1742 : 1452);
    case 2:
    default:
        return samples + (dsf ? 1264 : 1053);
    }
}