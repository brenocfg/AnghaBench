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
typedef  int uint64_t ;
typedef  int int64_t ;

/* Variables and functions */
 int UINT64_MAX ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t tta_check_crc64(uint8_t *pass)
{
    uint64_t crc = UINT64_MAX, poly = 0x42F0E1EBA9EA3693U;
    uint8_t *end = pass + strlen(pass);
    int i;

    while (pass < end) {
        crc ^= (uint64_t)*pass++ << 56;
        for (i = 0; i < 8; i++)
            crc = (crc << 1) ^ (poly & (((int64_t) crc) >> 63));
    }

    return crc ^ UINT64_MAX;
}