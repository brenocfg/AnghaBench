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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int /*<<< orphan*/ ) ; 
 int* crc_hi ; 
 int* crc_low ; 

__attribute__((used)) static uint16_t get_buffer_crc16( uint8_t * frame_ptr, uint16_t length )
{
    TEST_ASSERT( frame_ptr != NULL);

    uint8_t crc_hi_byte = 0xFF;
    uint8_t crc_low_byte = 0xFF;
    int index;

    while ( length-- )
    {
        index = crc_low_byte ^ *(frame_ptr++);
        crc_low_byte = crc_hi_byte ^ crc_hi[index];
        crc_hi_byte = crc_low[index];
    }
    return ((crc_hi_byte << 8) | crc_low_byte);
}