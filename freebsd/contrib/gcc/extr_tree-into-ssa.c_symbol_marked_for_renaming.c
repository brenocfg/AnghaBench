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

/* Variables and functions */
 int /*<<< orphan*/  DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 
 int bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syms_to_rename ; 

__attribute__((used)) static inline bool
symbol_marked_for_renaming (tree sym)
{
  gcc_assert (DECL_P (sym));
  return bitmap_bit_p (syms_to_rename, DECL_UID (sym));
}