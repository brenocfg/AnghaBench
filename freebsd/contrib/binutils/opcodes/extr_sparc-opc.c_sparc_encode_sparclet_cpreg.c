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
 int lookup_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sparclet_cpreg_table ; 

int
sparc_encode_sparclet_cpreg (const char *name)
{
  return lookup_name (sparclet_cpreg_table, name);
}