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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_class_type ; 
 int /*<<< orphan*/  popclass () ; 

void
pop_nested_class (void)
{
  tree context = DECL_CONTEXT (TYPE_MAIN_DECL (current_class_type));

  popclass ();
  if (context && CLASS_TYPE_P (context))
    pop_nested_class ();
}