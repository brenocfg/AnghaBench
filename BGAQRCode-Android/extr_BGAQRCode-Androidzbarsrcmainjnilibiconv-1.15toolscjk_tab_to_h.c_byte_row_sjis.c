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

__attribute__((used)) static int byte_row_sjis (int byte) {
  if (byte >= 0x81 && byte < 0xa0)
    return byte-0x81;
  else if (byte >= 0xe0)
    return byte-0xc1;
  else
    return -1;
}