#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
struct fun_macro {size_t* args; scalar_t__ argc; int /*<<< orphan*/  const* offset; TYPE_5__* node; int /*<<< orphan*/  buff; } ;
struct TYPE_10__ {int base; } ;
struct TYPE_13__ {TYPE_1__ out; } ;
typedef  TYPE_4__ cpp_reader ;
struct TYPE_12__ {TYPE_2__* macro; } ;
struct TYPE_14__ {TYPE_3__ value; } ;
typedef  TYPE_5__ cpp_hashnode ;
struct TYPE_11__ {int paramc; } ;

/* Variables and functions */
 scalar_t__ BUFF_FRONT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cpp_get_buff (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  _cpp_release_buff (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
maybe_start_funlike (cpp_reader *pfile, cpp_hashnode *node, const uchar *start, struct fun_macro *macro)
{
  unsigned int n = node->value.macro->paramc + 1;

  if (macro->buff)
    _cpp_release_buff (pfile, macro->buff);
  macro->buff = _cpp_get_buff (pfile, n * sizeof (size_t));
  macro->args = (size_t *) BUFF_FRONT (macro->buff);
  macro->node = node;
  macro->offset = start - pfile->out.base;
  macro->argc = 0;
}