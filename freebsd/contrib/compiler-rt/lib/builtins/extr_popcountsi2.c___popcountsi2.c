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

si_int __popcountsi2(si_int a) {
  su_int x = (su_int)a;
  x = x - ((x >> 1) & 0x55555555);
  // Every 2 bits holds the sum of every pair of bits
  x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
  // Every 4 bits holds the sum of every 4-set of bits (3 significant bits)
  x = (x + (x >> 4)) & 0x0F0F0F0F;
  // Every 8 bits holds the sum of every 8-set of bits (4 significant bits)
  x = (x + (x >> 16));
  // The lower 16 bits hold two 8 bit sums (5 significant bits).
  //    Upper 16 bits are garbage
  return (x + (x >> 8)) & 0x0000003F; // (6 significant bits)
}