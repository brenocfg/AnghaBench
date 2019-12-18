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
struct TYPE_3__ {int c2t2; int c2t1; int /*<<< orphan*/  c0t2; int /*<<< orphan*/  c0t3; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */

__attribute__((used)) static void event2_pure(PokeyState* ps, int p5v, int p4v, int p917v)
{
    ps->c2t2 = !ps->c2t2;
    ps->c2t1 = p5v;
    /* high-pass clock for channel 0 */
    ps->c0t3 = ps->c0t2;
}