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
struct mips16_constant_pool {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CONSTANT_POOL_ADDRESS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ SYMBOL_REF ; 
 int /*<<< orphan*/  add_constant (struct mips16_constant_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LABEL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pool_constant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pool_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips16_rewrite_pool_refs (rtx *x, void *data)
{
  struct mips16_constant_pool *pool = data;
  if (GET_CODE (*x) == SYMBOL_REF && CONSTANT_POOL_ADDRESS_P (*x))
    *x = gen_rtx_LABEL_REF (Pmode, add_constant (pool,
						 get_pool_constant (*x),
						 get_pool_mode (*x)));
  return 0;
}