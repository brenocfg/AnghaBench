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
 int AV_RB16 (int const*) ; 
 int PVA_MAGIC ; 
 int PVA_MAX_PAYLOAD_LENGTH ; 

__attribute__((used)) static int pva_check(const uint8_t *p) {
    int length = AV_RB16(p + 6);
    if (AV_RB16(p) != PVA_MAGIC || !p[2] || p[2] > 2 || p[4] != 0x55 ||
        (p[5] & 0xe0) || length > PVA_MAX_PAYLOAD_LENGTH)
        return -1;
    return length + 8;
}