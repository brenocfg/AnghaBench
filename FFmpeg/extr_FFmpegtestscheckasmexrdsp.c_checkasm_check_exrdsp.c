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
struct TYPE_3__ {int /*<<< orphan*/  predictor; int /*<<< orphan*/  reorder_pixels; } ;
typedef  TYPE_1__ ExrDSPContext ;

/* Variables and functions */
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_predictor () ; 
 int /*<<< orphan*/  check_reorder_pixels () ; 
 int /*<<< orphan*/  ff_exrdsp_init (TYPE_1__*) ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_exrdsp(void)
{
    ExrDSPContext h;

    ff_exrdsp_init(&h);

    if (check_func(h.reorder_pixels, "reorder_pixels"))
        check_reorder_pixels();

    report("reorder_pixels");

    if (check_func(h.predictor, "predictor"))
        check_predictor();

    report("predictor");
}