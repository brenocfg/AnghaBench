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
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 

__attribute__((used)) static inline int
validate_sig (int sig)
{
    int i, sum = 0, emin = 0, sig0 = 0, sig1 = 0;
    dbprintf(3, " sum=0");
    for(i = 3; --i >= 0; ) {
        int e = sig & 3;
        sig >>= 2;
        sum = e - sum;
        sig1 <<= 4;
        sig1 += sum;
        dbprintf(3, "%d", sum);
        if(!i)
            break;

        e = sig & 3;
        sig >>= 2;
        sum = e - sum;
        sig0 <<= 4;
        if(emin > sum)
            emin = sum;
        sig0 += sum;
        dbprintf(3, "%d", sum);
    }

    dbprintf(3, " emin=%d sig=%03x/%03x", emin, sig1 & 0xfff, sig0 & 0xfff);

    emin = emin + (emin << 4) + (emin << 8);
    sig0 -= emin;
    sig1 += emin;

    dbprintf(3, "=%03x/%03x", sig1 & 0xfff, sig0 & 0xfff);
    return((sig0 | sig1) & 0x888);
}