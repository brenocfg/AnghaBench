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
 int /*<<< orphan*/  PATH_MAX ; 
 int strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compare_str(const void *a, const void *b)
{
    return strncmp(*(const char**)a, *(const char**)b, PATH_MAX);
}