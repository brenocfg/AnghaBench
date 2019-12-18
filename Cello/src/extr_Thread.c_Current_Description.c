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

__attribute__((used)) static const char* Current_Description(void) {
  return
    "The `Current` class can be implemented by types which have implicit "
    "instances associated with them. For example it can be used to retrieve "
    "the _current_ `Thread`, or it could be used to get the _current_ Garbage "
    "Collector."
    "\n\n"
    "This class may be implemented by types which express the [Singleton "
    "Design Pattern](http://en.wikipedia.org/wiki/Singleton_pattern)";
}