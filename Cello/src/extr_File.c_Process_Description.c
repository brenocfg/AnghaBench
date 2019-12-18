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

__attribute__((used)) static const char* Process_Description(void) {
  return 
    "The `Process` type is a wrapper for an operating system process as "
    "constructed by the unix-like call `popen`. In this sense it is much like "
    "a standard file in the operating system but that instead of writing data "
    "to a location you are writing it as input to a process.";
}