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
 int MAX_PATH ; 
 int /*<<< orphan*/  _fullpath (char*,char*,int) ; 
 int /*<<< orphan*/  path_copy (char*,char*) ; 

void path_absolute(char path[MAX_PATH]) {
    char rel_path[MAX_PATH];
    path_copy(rel_path, path);
    _fullpath(path, rel_path, MAX_PATH);
}