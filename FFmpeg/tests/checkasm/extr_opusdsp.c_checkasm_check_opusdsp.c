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
struct TYPE_3__ {int /*<<< orphan*/  deemphasis; int /*<<< orphan*/  postfilter; } ;
typedef  TYPE_1__ OpusDSP ;

/* Variables and functions */
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_opus_dsp_init (TYPE_1__*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  test_deemphasis () ; 
 int /*<<< orphan*/  test_postfilter (int) ; 

void checkasm_check_opusdsp(void)
{
    OpusDSP ctx;
    ff_opus_dsp_init(&ctx);

    if (check_func(ctx.postfilter, "postfilter_15"))
        test_postfilter(15);
    report("postfilter_15");

    if (check_func(ctx.postfilter, "postfilter_512"))
        test_postfilter(512);
    report("postfilter_512");

    if (check_func(ctx.postfilter, "postfilter_1022"))
        test_postfilter(1022);
    report("postfilter_1022");

    if (check_func(ctx.deemphasis, "deemphasis"))
        test_deemphasis();
    report("deemphasis");
}