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
 int PAGE_SIZE ; 

uint32_t
hibernate_sum_page(uint8_t *buf, uint32_t ppnum)
{
    return (((uint32_t *)buf)[((PAGE_SIZE >> 2) - 1) & ppnum]);
}