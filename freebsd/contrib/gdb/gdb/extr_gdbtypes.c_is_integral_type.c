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
 scalar_t__ TYPE_CODE_BOOL ; 
 scalar_t__ TYPE_CODE_CHAR ; 
 scalar_t__ TYPE_CODE_ENUM ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_CODE_RANGE ; 

int
is_integral_type (struct type *t)
{
  CHECK_TYPEDEF (t);
  return
    ((t != NULL)
     && ((TYPE_CODE (t) == TYPE_CODE_INT)
	 || (TYPE_CODE (t) == TYPE_CODE_ENUM)
	 || (TYPE_CODE (t) == TYPE_CODE_CHAR)
	 || (TYPE_CODE (t) == TYPE_CODE_RANGE)
	 || (TYPE_CODE (t) == TYPE_CODE_BOOL)));
}