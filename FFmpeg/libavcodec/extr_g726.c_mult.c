#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_4__ {int exp; int mant; int sign; } ;
typedef  TYPE_1__ Float11 ;

/* Variables and functions */

__attribute__((used)) static inline int16_t mult(Float11* f1, Float11* f2)
{
        int res, exp;

        exp = f1->exp + f2->exp;
        res = (((f1->mant * f2->mant) + 0x30) >> 4);
        res = exp > 19 ? res << (exp - 19) : res >> (19 - exp);
        return (f1->sign ^ f2->sign) ? -res : res;
}