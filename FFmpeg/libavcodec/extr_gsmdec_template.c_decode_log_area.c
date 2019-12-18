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
 int gsm_mult (int,int) ; 

__attribute__((used)) static inline int decode_log_area(int coded, int factor, int offset)
{
    coded <<= 10;
    coded -= offset;
    return gsm_mult(coded, factor) * 2;
}