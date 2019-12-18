#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_3__ {scalar_t__ (* type_for_size ) (int,int) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
 scalar_t__ error_mark_node ; 
 TYPE_2__ lang_hooks ; 
 scalar_t__ stub1 (int,int) ; 

tree
builtin_type_for_size (int size, bool unsignedp)
{
  tree type = lang_hooks.types.type_for_size (size, unsignedp);
  return type ? type : error_mark_node;
}