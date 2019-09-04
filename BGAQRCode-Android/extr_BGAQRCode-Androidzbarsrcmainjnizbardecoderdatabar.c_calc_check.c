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

/* Variables and functions */
 int /*<<< orphan*/  dbprintf (int,char*,unsigned int) ; 

__attribute__((used)) static inline unsigned
calc_check (unsigned sig0,
            unsigned sig1,
            unsigned side,
            unsigned mod)
{
    unsigned chk = 0;
    int i;
    for(i = 4; --i >= 0; ) {
        chk = (chk * 3 + (sig1 & 0xf) + 1) * 3 + (sig0 & 0xf) + 1;
        sig1 >>= 4;
        sig0 >>= 4;
        if(!(i & 1))
            chk %= mod;
    }
    dbprintf(2, " chk=%d", chk);

    if(side)
        chk = (chk * (6561 % mod)) % mod;
    return(chk);
}