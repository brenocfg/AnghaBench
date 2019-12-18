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
 size_t CLAMP_MAX (int,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  add_package_search_path (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

void add_package_search_path_range(const char *start, const char *end) {
    char path[MAX_PATH];
    size_t len = CLAMP_MAX(end - start, MAX_PATH - 1);
    memcpy(path, start, len);
    path[len] = 0;
    add_package_search_path(path);
}