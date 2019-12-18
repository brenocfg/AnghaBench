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

__attribute__((used)) static int
getBITS (unsigned char *ptr, int *idx, int size, int max)
{
  int byte = *idx / 8;
  int bit = *idx % 8;

  if (byte >= max)
    return 0;

  *idx += size;

  return (ptr[byte] >> (8 - bit - size)) & ((1 << size) - 1);
}