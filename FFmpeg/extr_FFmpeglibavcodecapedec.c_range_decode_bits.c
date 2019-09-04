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
typedef  int /*<<< orphan*/  APEContext ;

/* Variables and functions */
 int range_decode_culshift (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  range_decode_update (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int range_decode_bits(APEContext *ctx, int n)
{
    int sym = range_decode_culshift(ctx, n);
    range_decode_update(ctx, 1, sym);
    return sym;
}