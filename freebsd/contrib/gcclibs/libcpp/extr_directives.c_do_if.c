#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  skipping; } ;
struct TYPE_7__ {int /*<<< orphan*/  mi_ind_cmacro; TYPE_1__ state; } ;
typedef  TYPE_2__ cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  T_IF ; 
 int _cpp_parse_expr (TYPE_2__*) ; 
 int /*<<< orphan*/  push_conditional (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_if (cpp_reader *pfile)
{
  int skip = 1;

  if (! pfile->state.skipping)
    skip = _cpp_parse_expr (pfile) == false;

  push_conditional (pfile, skip, T_IF, pfile->mi_ind_cmacro);
}