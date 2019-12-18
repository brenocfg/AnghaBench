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
 scalar_t__ BIT_POS (int,int) ; 
 int BIT_STR (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void decode_1p_track(int *out, int code, int m, int off)
{
    int pos = BIT_STR(code, 0, m) + off; ///code: m+1 bits

    out[0] = BIT_POS(code, m) ? -pos : pos;
}