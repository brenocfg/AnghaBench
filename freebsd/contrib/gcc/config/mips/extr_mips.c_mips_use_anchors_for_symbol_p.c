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

/* Variables and functions */
#define  SYMBOL_CONSTANT_POOL 129 
#define  SYMBOL_SMALL_DATA 128 
 int mips_classify_symbol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mips_use_anchors_for_symbol_p (rtx symbol)
{
  switch (mips_classify_symbol (symbol))
    {
    case SYMBOL_CONSTANT_POOL:
    case SYMBOL_SMALL_DATA:
      return false;

    default:
      return true;
    }
}