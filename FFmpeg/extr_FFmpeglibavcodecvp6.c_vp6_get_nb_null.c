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
struct TYPE_3__ {int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ VP56Context ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned vp6_get_nb_null(VP56Context *s)
{
    unsigned val = get_bits(&s->gb, 2);
    if (val == 2)
        val += get_bits(&s->gb, 2);
    else if (val == 3) {
        val = get_bits1(&s->gb) << 2;
        val = 6+val + get_bits(&s->gb, 2+val);
    }
    return val;
}