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
struct TYPE_3__ {scalar_t__ offset; scalar_t__ range; } ;
typedef  TYPE_1__ ProbRange ;
typedef  int /*<<< orphan*/  BigInt ;

/* Variables and functions */
 int /*<<< orphan*/  ff_big_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ff_big_div (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ff_big_mul (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int pop_integer(BigInt *b, const ProbRange *pranges)
{
    uint8_t r;
    int i;

    /* extract the last byte into r, and shift right b by 8 bits */
    ff_big_div(b, 0, &r);

    i = 0;
    while (r < pranges->offset || r >= pranges->range + pranges->offset) {
        pranges++;
        i++;
    }
    ff_big_mul(b, pranges->range);
    ff_big_add(b, r - pranges->offset);
    return i;
}