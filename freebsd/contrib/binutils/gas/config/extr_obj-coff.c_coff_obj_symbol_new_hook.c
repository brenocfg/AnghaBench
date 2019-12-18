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
 int /*<<< orphan*/  SF_SET_LOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SF_SET_STRING (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_LOCAL (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_DATA_TYPE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_SET_NUMBER_AUXILIARY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_SET_STORAGE_CLASS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_NULL ; 
 TYPE_1__* coffsymbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  symbol_get_bfdsym (int /*<<< orphan*/ *) ; 
 char* xmalloc (long) ; 

void
coff_obj_symbol_new_hook (symbolS *symbolP)
{
  long   sz = (OBJ_COFF_MAX_AUXENTRIES + 1) * sizeof (combined_entry_type);
  char * s  = xmalloc (sz);

  memset (s, 0, sz);
  coffsymbol (symbol_get_bfdsym (symbolP))->native = (combined_entry_type *) s;

  S_SET_DATA_TYPE (symbolP, T_NULL);
  S_SET_STORAGE_CLASS (symbolP, 0);
  S_SET_NUMBER_AUXILIARY (symbolP, 0);

  if (S_IS_STRING (symbolP))
    SF_SET_STRING (symbolP);

  if (S_IS_LOCAL (symbolP))
    SF_SET_LOCAL (symbolP);
}