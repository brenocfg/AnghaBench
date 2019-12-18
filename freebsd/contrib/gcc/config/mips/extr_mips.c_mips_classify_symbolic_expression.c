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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum mips_symbol_type { ____Placeholder_mips_symbol_type } mips_symbol_type ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ UNSPEC_ADDRESS_P (int /*<<< orphan*/ ) ; 
 int UNSPEC_ADDRESS_TYPE (int /*<<< orphan*/ ) ; 
 int mips_classify_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_split_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum mips_symbol_type
mips_classify_symbolic_expression (rtx x)
{
  HOST_WIDE_INT offset;

  mips_split_const (x, &x, &offset);
  if (UNSPEC_ADDRESS_P (x))
    return UNSPEC_ADDRESS_TYPE (x);

  return mips_classify_symbol (x);
}