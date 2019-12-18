#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* context; } ;
typedef  TYPE_4__ cpp_reader ;
struct TYPE_9__ {TYPE_2__* macro; } ;
struct TYPE_11__ {TYPE_3__ value; } ;
typedef  TYPE_5__ cpp_hashnode ;
struct TYPE_8__ {scalar_t__ syshdr; } ;
struct TYPE_7__ {TYPE_5__* macro; } ;

/* Variables and functions */

int
cpp_sys_macro_p (cpp_reader *pfile)
{
  cpp_hashnode *node = pfile->context->macro;

  return node && node->value.macro && node->value.macro->syshdr;
}