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
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  combined_entry_type ;
struct TYPE_2__ {int /*<<< orphan*/ * native; } ;

/* Variables and functions */
 int OBJ_COFF_MAX_AUXENTRIES ; 
 int /*<<< orphan*/  SF_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SF_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* coffsymbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  symbol_get_bfdsym (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmalloc (long) ; 

void
coff_obj_symbol_clone_hook (symbolS *newsymP, symbolS *orgsymP)
{
  long sz = (OBJ_COFF_MAX_AUXENTRIES + 1) * sizeof (combined_entry_type);
  combined_entry_type * s = xmalloc (sz);

  memcpy (s, coffsymbol (symbol_get_bfdsym (orgsymP))->native, sz);
  coffsymbol (symbol_get_bfdsym (newsymP))->native = s;

  SF_SET (newsymP, SF_GET (orgsymP));
}