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
 int /*<<< orphan*/  save_string (char const*,int) ; 
 int /*<<< orphan*/  std_prefix ; 

void
set_std_prefix (const char *prefix, int len)
{
  std_prefix = save_string (prefix, len);
}