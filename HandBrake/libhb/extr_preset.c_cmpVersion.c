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

__attribute__((used)) static int cmpVersion(int a_major, int a_minor, int a_micro,
                      int b_major, int b_minor, int b_micro)
{
    if (a_major > b_major) return 1;
    if (a_major < b_major) return -1;
    if (a_minor > b_minor) return 1;
    if (a_minor < b_minor) return -1;
    if (a_micro > b_micro) return 1;
    if (a_micro < b_micro) return -1;
    return 0;
}