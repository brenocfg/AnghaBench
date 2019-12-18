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
typedef  int /*<<< orphan*/  etree_type ;

/* Variables and functions */
 int /*<<< orphan*/  address ; 
 int /*<<< orphan*/  mri_add_to_list (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mri_output_section (const char *name, etree_type *vma)
{
  mri_add_to_list (&address, name, vma, 0, 0, 0);
}