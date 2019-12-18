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
typedef  scalar_t__ tu_int ;
typedef  scalar_t__ ti_int ;

/* Variables and functions */
 int /*<<< orphan*/  compilerrt_abort () ; 

ti_int __subvti3(ti_int a, ti_int b) {
  ti_int s = (tu_int)a - (tu_int)b;
  if (b >= 0) {
    if (s > a)
      compilerrt_abort();
  } else {
    if (s <= a)
      compilerrt_abort();
  }
  return s;
}