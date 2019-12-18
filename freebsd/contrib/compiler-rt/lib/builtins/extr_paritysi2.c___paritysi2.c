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
typedef  int si_int ;

/* Variables and functions */

si_int __paritysi2(si_int a) {
  su_int x = (su_int)a;
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  return (0x6996 >> (x & 0xF)) & 1;
}