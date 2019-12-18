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
 scalar_t__ INT_CST_LT_UNSIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ALIGN_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_in_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizetype ; 

tree
default_cxx_get_cookie_size (tree type)
{
  tree cookie_size;

  /* We need to allocate an additional max (sizeof (size_t), alignof
     (true_type)) bytes.  */
  tree sizetype_size;
  tree type_align;

  sizetype_size = size_in_bytes (sizetype);
  type_align = size_int (TYPE_ALIGN_UNIT (type));
  if (INT_CST_LT_UNSIGNED (type_align, sizetype_size))
    cookie_size = sizetype_size;
  else
    cookie_size = type_align;

  return cookie_size;
}