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
typedef  int hashval_t ;

/* Variables and functions */

__attribute__((used)) static hashval_t
hashmem (const void *p_p, size_t sz)
{
  const unsigned char *p = (const unsigned char *)p_p;
  size_t i;
  hashval_t h;

  h = 0;
  for (i = 0; i < sz; i++)
    h = h * 67 - (*p++ - 113);
  return h;
}