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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_VOID ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 

int
can_dereference (struct type *t)
{
  /* FIXME: Should we return true for references as well as pointers?  */
  CHECK_TYPEDEF (t);
  return
    (t != NULL
     && TYPE_CODE (t) == TYPE_CODE_PTR
     && TYPE_CODE (TYPE_TARGET_TYPE (t)) != TYPE_CODE_VOID);
}