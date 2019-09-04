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
typedef  scalar_t__ int64 ;

/* Variables and functions */

bool JSINT64_IS_NEGZERO(int64 l) {
  union {
    int64 i;
    double d;
  } x;
  if (l != 0) return false;
  x.i = l;
  return x.d == -0;
}