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
 scalar_t__ base ; 
 int /*<<< orphan*/  lang_add_input_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_input_file_is_file_enum ; 

void
mri_load (const char *name)
{
  base = 0;
  lang_add_input_file (name, lang_input_file_is_file_enum, NULL);
}