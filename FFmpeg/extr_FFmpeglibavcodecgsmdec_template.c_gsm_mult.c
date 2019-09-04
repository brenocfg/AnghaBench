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
typedef  int SUINT ;

/* Variables and functions */

__attribute__((used)) static inline int gsm_mult(int a, int b)
{
    return (int)(a * (SUINT)b + (1 << 14)) >> 15;
}