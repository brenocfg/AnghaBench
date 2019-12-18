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

/* Variables and functions */
 int UICR0 ; 
 int UICR1 ; 

__attribute__((used)) static void pio_irq_disable(int bEndpointAddress)
{
        bEndpointAddress &= 0xf;
        if (bEndpointAddress < 8)
                UICR0 |= 1 << bEndpointAddress;
        else {
                bEndpointAddress -= 8;
                UICR1 |= 1 << bEndpointAddress;
        }
}