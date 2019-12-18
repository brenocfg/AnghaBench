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
struct TYPE_3__ {int /*<<< orphan*/ * mct_decode; } ;
typedef  TYPE_1__ Jpeg2000DSPContext ;

/* Variables and functions */
 size_t FF_DWT53 ; 
 size_t FF_DWT97 ; 
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_ict_float () ; 
 int /*<<< orphan*/  check_rct_int () ; 
 int /*<<< orphan*/  ff_jpeg2000dsp_init (TYPE_1__*) ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_jpeg2000dsp(void)
{
    Jpeg2000DSPContext h;

    ff_jpeg2000dsp_init(&h);

    if (check_func(h.mct_decode[FF_DWT53], "jpeg2000_rct_int"))
        check_rct_int();
    if (check_func(h.mct_decode[FF_DWT97], "jpeg2000_ict_float"))
        check_ict_float();

    report("mct_decode");
}