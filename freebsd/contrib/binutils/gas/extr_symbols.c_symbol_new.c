#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  valueT ;
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  segT ;
typedef  int /*<<< orphan*/  fragS ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  symbol_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_lastP ; 
 int /*<<< orphan*/  symbol_rootP ; 

symbolS *
symbol_new (const char *name, segT segment, valueT valu, fragS *frag)
{
  symbolS *symbolP = symbol_create (name, segment, valu, frag);

  /* Link to end of symbol chain.  */
  {
    extern int symbol_table_frozen;
    if (symbol_table_frozen)
      abort ();
  }
  symbol_append (symbolP, symbol_lastP, &symbol_rootP, &symbol_lastP);

  return symbolP;
}