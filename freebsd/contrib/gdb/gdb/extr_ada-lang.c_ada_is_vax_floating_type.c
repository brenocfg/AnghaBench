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
 scalar_t__ DEPRECATED_STREQN (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_CODE_RANGE ; 
 int /*<<< orphan*/ * ada_type_name (struct type*) ; 
 int strlen (int /*<<< orphan*/ *) ; 

int
ada_is_vax_floating_type (struct type *type)
{
  int name_len =
    (ada_type_name (type) == NULL) ? 0 : strlen (ada_type_name (type));
  return
    name_len > 6
    && (TYPE_CODE (type) == TYPE_CODE_INT
	|| TYPE_CODE (type) == TYPE_CODE_RANGE)
    && DEPRECATED_STREQN (ada_type_name (type) + name_len - 6, "___XF", 5);
}