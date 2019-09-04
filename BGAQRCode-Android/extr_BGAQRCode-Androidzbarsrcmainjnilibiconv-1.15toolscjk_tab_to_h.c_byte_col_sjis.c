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

__attribute__((used)) static int byte_col_sjis (int byte) {
  if (byte >= 0x40 && byte < 0x7f)
    return byte-0x40;
  else if (byte >= 0x80 && byte < 0xfd)
    return byte-0x41;
  else
    return -1;
}