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

__attribute__((used)) static const char* Thread_Description(void) {
  return
    "The `Thread` type provides a basic primitive for concurrent "
    "execution. It acts as a basic wrapper around operating system threads, "
    "using WinThreads on Windows and pthreads otherwise.";
}