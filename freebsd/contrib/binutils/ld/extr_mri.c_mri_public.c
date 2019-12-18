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
 int /*<<< orphan*/  exp_assop (char,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_add_assignment (int /*<<< orphan*/ ) ; 

void
mri_public (const char *name, etree_type *exp)
{
  lang_add_assignment (exp_assop ('=', name, exp));
}