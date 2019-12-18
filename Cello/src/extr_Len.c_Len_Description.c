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

__attribute__((used)) static const char* Len_Description(void) {
  return
    "The `Len` class can be implemented by any type that has a length "
    "associated with it. It is typically implemented by collections "
    "and is often used in conjunction with `Iter` or `Get`.";
}