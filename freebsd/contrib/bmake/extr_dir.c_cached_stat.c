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
 int cached_stats (int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtimes ; 

int
cached_stat(const char *pathname, void *st)
{
    return cached_stats(&mtimes, pathname, st, 0);
}