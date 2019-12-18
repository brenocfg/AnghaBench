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
 int MASK_TWENTY_SEVEN ; 

uint8_t _double_byte(uint8_t a)
{
    return ((a << 1) ^ ((a >> 7) * MASK_TWENTY_SEVEN));
}