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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_MODE (int /*<<< orphan*/ ) ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_raw_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static rtx
produce_memory_decl_rtl (tree obj, int *regno)
{
  rtx x;
  
  gcc_assert (obj);
  if (TREE_STATIC (obj) || DECL_EXTERNAL (obj))
    {
      const char *name = IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (obj));
      x = gen_rtx_SYMBOL_REF (Pmode, name);
    }
  else
    x = gen_raw_REG (Pmode, (*regno)++);

  return gen_rtx_MEM (DECL_MODE (obj), x);
}