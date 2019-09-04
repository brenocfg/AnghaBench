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

__attribute__((used)) static int byte_col_big5 (int byte) {
  if (byte >= 0x40 && byte < 0x7f)
    return byte-0x40;
  else if (byte >= 0xa1 && byte < 0xff)
    return byte-0x62;
  else
    return -1;
}