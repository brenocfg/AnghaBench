#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int a; scalar_t__ overread; int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ ArithCoder ;

/* Variables and functions */
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ac_init(ArithCoder *ac, GetBitContext *gb)
{
    ac->a = 4095;
    ac->c = get_bits(gb, 12);
    ac->overread = 0;
}