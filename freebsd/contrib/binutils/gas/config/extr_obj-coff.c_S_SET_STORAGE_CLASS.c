#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_8__ {TYPE_3__* native; } ;
struct TYPE_5__ {int n_sclass; } ;
struct TYPE_6__ {TYPE_1__ syment; } ;
struct TYPE_7__ {TYPE_2__ u; } ;

/* Variables and functions */
 TYPE_4__* coffsymbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_get_bfdsym (int /*<<< orphan*/ *) ; 

int
S_SET_STORAGE_CLASS (symbolS *sym, int val)
{
  coffsymbol (symbol_get_bfdsym (sym))->native->u.syment.n_sclass = val;
  return val;
}