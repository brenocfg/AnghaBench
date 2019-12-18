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
 int /*<<< orphan*/  add_language (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pascal_language_defn ; 

void
_initialize_pascal_language (void)
{
  add_language (&pascal_language_defn);
}