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
 int /*<<< orphan*/  std_include_path ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ ,char*) ; 

void add_include_path(char *path) {
    vec_push(std_include_path, path);
}