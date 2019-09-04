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
 int /*<<< orphan*/  assert (char*) ; 
 scalar_t__ malloc (int) ; 

char* test() {
  // allocate more memory than we currently have, forcing a growth
  char* buffer = (char*)malloc(64 * 1024 * 1024);
  assert(buffer);
  *buffer = 42;
  return buffer;
}