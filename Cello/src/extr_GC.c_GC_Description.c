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

__attribute__((used)) static const char* GC_Description(void) {
  return
    "The `GC` type provides an interface to the Cello Garbage Collector. One "
    "instance of this type is created for each thread and can be retrieved "
    "using the `current` function. The Garbage Collector can be stopped and "
    "started using `start` and `stop` and objects can be added or removed from "
    "the Garbage Collector using `set` and `rem`.";
}