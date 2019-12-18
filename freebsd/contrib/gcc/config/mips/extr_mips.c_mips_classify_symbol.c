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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum mips_symbol_type { ____Placeholder_mips_symbol_type } mips_symbol_type ;
struct TYPE_2__ {scalar_t__ (* binds_local_p ) (scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ CONSTANT_POOL_ADDRESS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 int SYMBOL_CONSTANT_POOL ; 
 int SYMBOL_GENERAL ; 
 int SYMBOL_GOT_GLOBAL ; 
 int SYMBOL_GOT_LOCAL ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_REF_LOCAL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF_SMALL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF_TLS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_REF_WEAK (int /*<<< orphan*/ ) ; 
 int SYMBOL_SMALL_DATA ; 
 int SYMBOL_TLS ; 
 scalar_t__ TARGET_ABICALLS ; 
 scalar_t__ TARGET_ABSOLUTE_ABICALLS ; 
 scalar_t__ TARGET_MIPS16 ; 
 scalar_t__ TREE_PUBLIC (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_pool_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ mips_section_threshold ; 
 scalar_t__ stub1 (scalar_t__) ; 
 TYPE_1__ targetm ; 

__attribute__((used)) static enum mips_symbol_type
mips_classify_symbol (rtx x)
{
  if (GET_CODE (x) == LABEL_REF)
    {
      if (TARGET_MIPS16)
	return SYMBOL_CONSTANT_POOL;
      if (TARGET_ABICALLS && !TARGET_ABSOLUTE_ABICALLS)
	return SYMBOL_GOT_LOCAL;
      return SYMBOL_GENERAL;
    }

  gcc_assert (GET_CODE (x) == SYMBOL_REF);

  if (SYMBOL_REF_TLS_MODEL (x))
    return SYMBOL_TLS;

  if (CONSTANT_POOL_ADDRESS_P (x))
    {
      if (TARGET_MIPS16)
	return SYMBOL_CONSTANT_POOL;

      if (GET_MODE_SIZE (get_pool_mode (x)) <= mips_section_threshold)
	return SYMBOL_SMALL_DATA;
    }

  /* Do not use small-data accesses for weak symbols; they may end up
     being zero.  */
  if (SYMBOL_REF_SMALL_P (x)
      && !SYMBOL_REF_WEAK (x))
    return SYMBOL_SMALL_DATA;

  if (TARGET_ABICALLS)
    {
      if (SYMBOL_REF_DECL (x) == 0)
	{
	  if (!SYMBOL_REF_LOCAL_P (x))
	    return SYMBOL_GOT_GLOBAL;
	}
      else
	{
	  /* Don't use GOT accesses for locally-binding symbols if
	     TARGET_ABSOLUTE_ABICALLS.  Otherwise, there are three
	     cases to consider:

		- o32 PIC (either with or without explicit relocs)
		- n32/n64 PIC without explicit relocs
		- n32/n64 PIC with explicit relocs

	     In the first case, both local and global accesses will use an
	     R_MIPS_GOT16 relocation.  We must correctly predict which of
	     the two semantics (local or global) the assembler and linker
	     will apply.  The choice doesn't depend on the symbol's
	     visibility, so we deliberately ignore decl_visibility and
	     binds_local_p here.

	     In the second case, the assembler will not use R_MIPS_GOT16
	     relocations, but it chooses between local and global accesses
	     in the same way as for o32 PIC.

	     In the third case we have more freedom since both forms of
	     access will work for any kind of symbol.  However, there seems
	     little point in doing things differently.  */
	  if (DECL_P (SYMBOL_REF_DECL (x))
	      && TREE_PUBLIC (SYMBOL_REF_DECL (x))
	      && !(TARGET_ABSOLUTE_ABICALLS
		   && targetm.binds_local_p (SYMBOL_REF_DECL (x))))
	    return SYMBOL_GOT_GLOBAL;
	}

      if (!TARGET_ABSOLUTE_ABICALLS)
	return SYMBOL_GOT_LOCAL;
    }

  return SYMBOL_GENERAL;
}