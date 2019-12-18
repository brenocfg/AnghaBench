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
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static int
is_dynamic_field (struct type *templ_type, int field_num)
{
  const char *name = TYPE_FIELD_NAME (templ_type, field_num);
  return name != NULL
    && TYPE_CODE (TYPE_FIELD_TYPE (templ_type, field_num)) == TYPE_CODE_PTR
    && strstr (name, "___XVL") != NULL;
}