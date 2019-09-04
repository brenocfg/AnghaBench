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
typedef  int /*<<< orphan*/ * mallocer ;
typedef  int /*<<< orphan*/ * freeer ;

/* Variables and functions */
 int /*<<< orphan*/  RTLD_NOW ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dlopen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dlsym (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * freeproxy ; 
 int /*<<< orphan*/  handles ; 
 int /*<<< orphan*/ * lib_handle ; 
 int /*<<< orphan*/ * mallocproxy ; 

void get_lib() {
  //printf("get lib\n");
  lib_handle = dlopen("liblib.so", RTLD_NOW);
  assert(lib_handle != NULL);
  handles++;

  mallocproxy = (mallocer)dlsym(lib_handle, "mallocproxy");
  assert(mallocproxy!= NULL);
  freeproxy = (freeer)dlsym(lib_handle, "freeproxy");
  assert(freeproxy!= NULL);
}