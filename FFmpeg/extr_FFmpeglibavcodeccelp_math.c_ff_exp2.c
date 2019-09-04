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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int* exp2a ; 
 unsigned int* exp2b ; 

int ff_exp2(uint16_t power)
{
    unsigned int result= exp2a[power>>10] + 0x10000;

    av_assert2(power <= 0x7fff);

    result= (result<<3) + ((result*exp2b[(power>>5)&31])>>17);
    return result + ((result*(power&31)*89)>>22);
}