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

__attribute__((used)) static const char* Sort_Description(void) {
  return
    "The `Sort` class can be implemented by types which can be sorted in some "
    "way such as `Array`. By default the sorting function uses the `lt` method "
    "to compare elements, but a custom function can also be provided.";
}