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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ offset; int /*<<< orphan*/  range; } ;
typedef  TYPE_1__ ProbRange ;
typedef  int /*<<< orphan*/  BigInt ;

/* Variables and functions */
 int /*<<< orphan*/  ff_big_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ff_big_div (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ff_big_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void push_integer(BigInt *b, const ProbRange *prange)
{
    uint8_t r;

    ff_big_div(b, prange->range, &r);
    ff_big_mul(b, 0);
    ff_big_add(b, r + prange->offset);
}