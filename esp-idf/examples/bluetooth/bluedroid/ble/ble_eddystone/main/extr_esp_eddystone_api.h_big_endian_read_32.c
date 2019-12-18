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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  size_t pos ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t big_endian_read_32(const uint8_t *buffer, uint8_t pos)
{
    return (((uint32_t)buffer[pos]) << 24) | (((uint32_t)buffer[(pos)+1]) << 16) | (((uint32_t)buffer[(pos)+2]) << 8) | ((uint32_t)buffer[(pos)+3]);
}