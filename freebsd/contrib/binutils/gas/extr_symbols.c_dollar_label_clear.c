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
 scalar_t__ dollar_label_count ; 
 int /*<<< orphan*/  dollar_label_defines ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,unsigned int) ; 

void
dollar_label_clear (void)
{
  memset (dollar_label_defines, '\0', (unsigned int) dollar_label_count);
}