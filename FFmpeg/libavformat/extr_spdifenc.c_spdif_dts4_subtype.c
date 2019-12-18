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

__attribute__((used)) static int spdif_dts4_subtype(int period)
{
    switch (period) {
    case 512:   return 0x0;
    case 1024:  return 0x1;
    case 2048:  return 0x2;
    case 4096:  return 0x3;
    case 8192:  return 0x4;
    case 16384: return 0x5;
    }
    return -1;
}