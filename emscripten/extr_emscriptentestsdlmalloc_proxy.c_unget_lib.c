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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ *) ; 
 scalar_t__ handles ; 
 int /*<<< orphan*/ * lib_handle ; 

void unget_lib() {
  //printf("unget lib\n");
  assert(lib_handle);
  dlclose(lib_handle);
  handles--;
  if (handles == 0) lib_handle = NULL;
}