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
struct attr_desc {int is_numeric; int is_special; scalar_t__ default_val; scalar_t__ is_const; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int ATTR_SPECIAL ; 
 struct attr_desc* find_attr (char const**,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_attr_value (int /*<<< orphan*/ ,struct attr_desc*,int) ; 

__attribute__((used)) static void
make_internal_attr (const char *name, rtx value, int special)
{
  struct attr_desc *attr;

  attr = find_attr (&name, 1);
  gcc_assert (!attr->default_val);

  attr->is_numeric = 1;
  attr->is_const = 0;
  attr->is_special = (special & ATTR_SPECIAL) != 0;
  attr->default_val = get_attr_value (value, attr, -2);
}