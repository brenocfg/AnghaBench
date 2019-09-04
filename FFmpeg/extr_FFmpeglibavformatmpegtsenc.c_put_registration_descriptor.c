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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void put_registration_descriptor(uint8_t **q_ptr, uint32_t tag)
{
    uint8_t *q = *q_ptr;
    *q++ = 0x05; /* MPEG-2 registration descriptor*/
    *q++ = 4;
    *q++ = tag;
    *q++ = tag >> 8;
    *q++ = tag >> 16;
    *q++ = tag >> 24;
    *q_ptr = q;
}