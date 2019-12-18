#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* tree ;
struct TYPE_5__ {void* expr; } ;
struct TYPE_6__ {TYPE_1__ u; void* type; } ;
typedef  TYPE_2__ conversion ;

/* Variables and functions */
 TYPE_2__* alloc_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_ambig ; 

__attribute__((used)) static conversion *
build_ambiguous_conv (tree type, tree expr)
{
  conversion *c;

  c = alloc_conversion (ck_ambig);
  c->type = type;
  c->u.expr = expr;

  return c;
}