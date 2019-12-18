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
 int nybble (int const) ; 

__attribute__((used)) static uint8_t hex(const uint8_t *data, uint8_t *crc)
{
       uint8_t val = (nybble(data[0]) << 4) | nybble(data[1]);
       *crc += val;
       return val;
}