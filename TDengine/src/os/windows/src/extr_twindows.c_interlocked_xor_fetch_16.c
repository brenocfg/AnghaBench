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
 short _InterlockedXor16 (short volatile*,short) ; 

short interlocked_xor_fetch_16(short volatile* ptr, short val) {
  return _InterlockedXor16(ptr, val) ^ val;
}