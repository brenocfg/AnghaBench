#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_7__ {TYPE_5__* p; } ;
struct TYPE_8__ {TYPE_1__ x_tagndx; } ;
struct TYPE_9__ {TYPE_2__ x_sym; } ;
struct TYPE_10__ {TYPE_3__ auxent; } ;
struct TYPE_11__ {int fix_tag; TYPE_4__ u; } ;
typedef  TYPE_5__ combined_entry_type ;
struct TYPE_12__ {TYPE_5__* native; } ;

/* Variables and functions */
 TYPE_6__* coffsymbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_get_bfdsym (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
SA_SET_SYM_TAGNDX (symbolS *sym, symbolS *val)
{
  combined_entry_type *entry, *p;

  entry = &coffsymbol (symbol_get_bfdsym (sym))->native[1];
  p = coffsymbol (symbol_get_bfdsym (val))->native;
  entry->u.auxent.x_sym.x_tagndx.p = p;
  entry->fix_tag = 1;
}