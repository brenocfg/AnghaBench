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
 int /*<<< orphan*/  FFMIN (int,int) ; 
 int mpc8_dec_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mpc8_get_mask(GetBitContext *gb, int size, int t)
{
    int mask = 0;

    if(t && t != size)
         mask = mpc8_dec_enum(gb, FFMIN(t, size - t), size);
    if((t << 1) > size) mask = ~mask;

    return mask;
}