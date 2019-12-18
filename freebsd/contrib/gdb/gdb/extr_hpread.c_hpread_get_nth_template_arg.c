#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct type {int dummy; } ;
struct objfile {int dummy; } ;
struct TYPE_2__ {struct type* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FT_TEMPLATE_ARG ; 
 TYPE_1__ TYPE_TEMPLATE_ARG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * current_template ; 
 struct type* lookup_fundamental_type (struct objfile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct type *
hpread_get_nth_template_arg (struct objfile *objfile, int n)
{
  if (current_template != NULL)
    return TYPE_TEMPLATE_ARG (current_template, n).type;
  else
    return lookup_fundamental_type (objfile, FT_TEMPLATE_ARG);
}