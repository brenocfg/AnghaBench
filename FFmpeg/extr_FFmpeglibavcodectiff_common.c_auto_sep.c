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

__attribute__((used)) static const char *auto_sep(int count, const char *sep, int i, int columns)
{
    if (sep)
        return i ? sep : "";
    if (i && i%columns) {
        return ", ";
    } else
        return columns < count ? "\n" : "";
}