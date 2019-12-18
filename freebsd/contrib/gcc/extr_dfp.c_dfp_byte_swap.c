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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
dfp_byte_swap (uint32_t in)
{
  uint32_t out = 0;
  unsigned char *p = (unsigned char *) &out;
  union {
    uint32_t i;
    unsigned char b[4];
  } u;

  u.i = in;
  p[0] = u.b[3];
  p[1] = u.b[2];
  p[2] = u.b[1];
  p[3] = u.b[0];

  return out;
}