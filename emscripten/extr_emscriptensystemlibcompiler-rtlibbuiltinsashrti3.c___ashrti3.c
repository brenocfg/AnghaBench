#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int high; int low; } ;
struct TYPE_4__ {int /*<<< orphan*/  all; TYPE_1__ s; } ;
typedef  TYPE_2__ twords ;
typedef  int /*<<< orphan*/  ti_int ;
typedef  int const si_int ;
typedef  int /*<<< orphan*/  di_int ;

/* Variables and functions */
 int CHAR_BIT ; 

ti_int
__ashrti3(ti_int a, si_int b)
{
    const int bits_in_dword = (int)(sizeof(di_int) * CHAR_BIT);
    twords input;
    twords result;
    input.all = a;
    if (b & bits_in_dword)  /* bits_in_dword <= b < bits_in_tword */
    {
        /* result.s.high = input.s.high < 0 ? -1 : 0 */
        result.s.high = input.s.high >> (bits_in_dword - 1);
        result.s.low = input.s.high >> (b - bits_in_dword);
    }
    else  /* 0 <= b < bits_in_dword */
    {
        if (b == 0)
            return a;
        result.s.high  = input.s.high >> b;
        result.s.low = (input.s.high << (bits_in_dword - b)) | (input.s.low >> b);
    }
    return result.all;
}