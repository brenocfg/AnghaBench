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
struct TYPE_3__ {int /*<<< orphan*/  apply_qmf; } ;
typedef  TYPE_1__ G722DSPContext ;

/* Variables and functions */
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_qmf () ; 
 int /*<<< orphan*/  ff_g722dsp_init (TYPE_1__*) ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_g722dsp(void)
{
    G722DSPContext h;

    ff_g722dsp_init(&h);

    if (check_func(h.apply_qmf, "g722_apply_qmf"))
        check_qmf();

    report("apply_qmf");
}