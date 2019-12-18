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
 int /*<<< orphan*/  get_bits_left (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_long (int /*<<< orphan*/ *,int) ; 
 unsigned int get_unary (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_rice_un(GetBitContext *gb, int k)
{
    unsigned int v = get_unary(gb, 1, get_bits_left(gb));
    return (v << k) | get_bits_long(gb, k);
}