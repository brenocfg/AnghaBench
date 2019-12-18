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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

void Cs2FADToMSF(u32 val, u8 *m, u8 *s, u8 *f)
{
   u32 temp;
   m[0] = val / 4500;
   temp = val % 4500;
   s[0] = temp / 75;
   f[0] = temp % 75;
}