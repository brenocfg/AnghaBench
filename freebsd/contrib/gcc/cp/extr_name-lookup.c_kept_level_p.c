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
struct TYPE_2__ {scalar_t__ blocks; scalar_t__ kind; scalar_t__ names; scalar_t__ keep; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 TYPE_1__* current_binding_level ; 
 scalar_t__ sk_cleanup ; 

bool
kept_level_p (void)
{
  return (current_binding_level->blocks != NULL_TREE
	  || current_binding_level->keep
	  || current_binding_level->kind == sk_cleanup
	  || current_binding_level->names != NULL_TREE);
}