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
 unsigned int get_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int get_linear(GetBitContext *gb, int n)
{
    unsigned int v = get_bits_long(gb, n);
    return (v >> 1) ^ -(v & 1);
}