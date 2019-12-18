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
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  offsetT ;
typedef  int /*<<< orphan*/  fragS ;
typedef  int /*<<< orphan*/  fixS ;
typedef  int /*<<< orphan*/  RELOC_ENUM ;

/* Variables and functions */
 int /*<<< orphan*/ * fix_new_internal (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

fixS *
fix_new (fragS *frag,		/* Which frag?  */
	 int where,			/* Where in that frag?  */
	 int size,			/* 1, 2, or 4 usually.  */
	 symbolS *add_symbol,	/* X_add_symbol.  */
	 offsetT offset,		/* X_add_number.  */
	 int pcrel,			/* TRUE if PC-relative relocation.  */
	 RELOC_ENUM r_type		/* Relocation type.  */)
{
  return fix_new_internal (frag, where, size, add_symbol,
			   (symbolS *) NULL, offset, pcrel, r_type);
}