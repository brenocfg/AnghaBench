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

__attribute__((used)) static const char* Filter_Description(void) {
  return
    "The `Filter` type can be used to filter the results of some iterable. "
    "Given a callable object `Filter` iterable returns only those items in "
    "the original iterable for where calling the function returns a "
    "non-`NULL` value.";
}