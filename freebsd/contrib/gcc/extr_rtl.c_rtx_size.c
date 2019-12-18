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
struct block_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 unsigned int RTX_CODE_SIZE (scalar_t__) ; 
 unsigned int RTX_HDR_SIZE ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_HAS_BLOCK_INFO_P (int /*<<< orphan*/ ) ; 

unsigned int
rtx_size (rtx x)
{
  if (GET_CODE (x) == SYMBOL_REF && SYMBOL_REF_HAS_BLOCK_INFO_P (x))
    return RTX_HDR_SIZE + sizeof (struct block_symbol);
  return RTX_CODE_SIZE (GET_CODE (x));
}