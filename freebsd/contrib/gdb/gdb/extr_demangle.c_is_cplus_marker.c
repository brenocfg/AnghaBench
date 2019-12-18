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
 int /*<<< orphan*/  cplus_markers ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,int) ; 

int
is_cplus_marker (int c)
{
  return c && strchr (cplus_markers, c) != NULL;
}