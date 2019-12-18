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
 int /*<<< orphan*/  assert (int) ; 
 char* get_gen_name_or_default (void const*,char*) ; 

const char *get_gen_name(const void *ptr) {
    const char *error = "ERROR";
    const char *name = get_gen_name_or_default(ptr, "error");
    assert(name != error);
    return name;
}