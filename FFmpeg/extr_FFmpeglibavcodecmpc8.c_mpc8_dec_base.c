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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int** mpc8_cnk_len ; 
 int** mpc8_cnk_lost ; 

__attribute__((used)) static inline int mpc8_dec_base(GetBitContext *gb, int k, int n)
{
    int len = mpc8_cnk_len[k-1][n-1] - 1;
    int code = len ? get_bits_long(gb, len) : 0;

    if (code >= mpc8_cnk_lost[k-1][n-1])
        code = ((code << 1) | get_bits1(gb)) - mpc8_cnk_lost[k-1][n-1];

    return code;
}