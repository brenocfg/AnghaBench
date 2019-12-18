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
 int /*<<< orphan*/ * ada_type_name (struct type*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ *,char*) ; 

int
ada_is_packed_array_type (struct type *type)
{
  if (type == NULL)
    return 0;
  CHECK_TYPEDEF (type);
  return
    ada_type_name (type) != NULL
    && strstr (ada_type_name (type), "___XP") != NULL;
}