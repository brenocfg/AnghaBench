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
 int ROUND_MUL16 (int,int) ; 
 int opus_ilog (int) ; 

__attribute__((used)) static inline int celt_log2tan(int isin, int icos)
{
    int lc, ls;
    lc = opus_ilog(icos);
    ls = opus_ilog(isin);
    icos <<= 15 - lc;
    isin <<= 15 - ls;
    return (ls << 11) - (lc << 11) +
           ROUND_MUL16(isin, ROUND_MUL16(isin, -2597) + 7932) -
           ROUND_MUL16(icos, ROUND_MUL16(icos, -2597) + 7932);
}