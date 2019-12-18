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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSTYPE_TEMPLATE_SPECIALIZATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uses_template_parms (int /*<<< orphan*/ ) ; 

bool
explicit_class_specialization_p (tree type)
{
  if (!CLASSTYPE_TEMPLATE_SPECIALIZATION (type))
    return false;
  return !uses_template_parms (CLASSTYPE_TI_ARGS (type));
}