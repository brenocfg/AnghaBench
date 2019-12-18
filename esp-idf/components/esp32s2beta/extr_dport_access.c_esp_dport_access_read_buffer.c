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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t DPORT_SEQUENCE_REG_READ (size_t) ; 

void esp_dport_access_read_buffer(uint32_t *buff_out, uint32_t address, uint32_t num_words)
{
    for (uint32_t i = 0;  i < num_words; ++i) {
        buff_out[i] = DPORT_SEQUENCE_REG_READ(address + i * 4);
    }
}