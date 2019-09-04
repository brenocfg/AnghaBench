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
typedef  int su_int ;
typedef  int du_int ;

/* Variables and functions */

du_int
__fixunsdfdi(double a)
{
    if (a <= 0.0) return 0;
    su_int high = a / 4294967296.f;               /* a / 0x1p32f; */
    su_int low = a - (double)high * 4294967296.f; /* high * 0x1p32f; */
    return ((du_int)high << 32) | low;
}