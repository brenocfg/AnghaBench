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
 int /*<<< orphan*/  declare_source_confusing (char const*) ; 

__attribute__((used)) static void
check_source (int cond, const char *clean_p)
{
  if (!cond)
    declare_source_confusing (clean_p);
}