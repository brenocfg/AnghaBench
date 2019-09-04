#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int (* get_model_sym ) (TYPE_2__*,int /*<<< orphan*/ *) ;int (* get_number ) (TYPE_2__*,int) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  pivot; int /*<<< orphan*/  edge_mode; } ;
typedef  TYPE_1__ SliceContext ;
typedef  TYPE_2__ ArithCoder ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int stub3 (TYPE_2__*,int) ; 

__attribute__((used)) static int decode_pivot(SliceContext *sc, ArithCoder *acoder, int base)
{
    int val, inv;

    inv = acoder->get_model_sym(acoder, &sc->edge_mode);
    val = acoder->get_model_sym(acoder, &sc->pivot) + 1;

    if (val > 2) {
        if ((base + 1) / 2 - 2 <= 0)
            return -1;

        val = acoder->get_number(acoder, (base + 1) / 2 - 2) + 3;
    }

    if ((unsigned)val >= base)
        return -1;

    return inv ? base - val : val;
}