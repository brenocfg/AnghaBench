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
 char* format (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *make_static_label(char *name) {
    static int c = 0;
    return format(".S%d.%s", c++, name);
}