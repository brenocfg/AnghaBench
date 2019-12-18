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
typedef  int /*<<< orphan*/  DiracArith ;

/* Variables and functions */
 scalar_t__ dirac_get_arith_bit (int /*<<< orphan*/ *,int) ; 
 int dirac_get_arith_uint (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int dirac_get_arith_int(DiracArith *c, int follow_ctx, int data_ctx)
{
    int ret = dirac_get_arith_uint(c, follow_ctx, data_ctx);
    if (ret && dirac_get_arith_bit(c, data_ctx+1))
        ret = -ret;
    return ret;
}