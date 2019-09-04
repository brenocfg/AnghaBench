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
 int /*<<< orphan*/  __cxa_thread_atexit (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __cxa_thread_atexit_impl (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanA ; 
 int /*<<< orphan*/  cleanB ; 
 int /*<<< orphan*/  cleanCarg ; 

int main() {
  atexit(cleanA);
  atexit(cleanB);
  __cxa_thread_atexit(cleanCarg, (void*)100, NULL);
  __cxa_thread_atexit_impl(cleanCarg, (void*)234, NULL);
  return 0;
}