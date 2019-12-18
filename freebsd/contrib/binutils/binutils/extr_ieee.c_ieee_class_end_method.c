#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee_handle {TYPE_3__* type_stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {TYPE_1__* classdef; } ;
struct TYPE_6__ {TYPE_2__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/ * method; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static bfd_boolean
ieee_class_end_method (void *p)
{
  struct ieee_handle *info = (struct ieee_handle *) p;

  assert (info->type_stack != NULL
	  && info->type_stack->type.classdef != NULL
	  && info->type_stack->type.classdef->method != NULL);

  info->type_stack->type.classdef->method = NULL;

  return TRUE;
}