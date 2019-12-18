#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* context; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_8__ {struct TYPE_8__* prev; scalar_t__ buff; TYPE_1__* macro; } ;
typedef  TYPE_3__ cpp_context ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DISABLED ; 
 int /*<<< orphan*/  _cpp_release_buff (TYPE_2__*,scalar_t__) ; 

void
_cpp_pop_context (cpp_reader *pfile)
{
  cpp_context *context = pfile->context;

  if (context->macro)
    context->macro->flags &= ~NODE_DISABLED;

  if (context->buff)
    _cpp_release_buff (pfile, context->buff);

  pfile->context = context->prev;
}