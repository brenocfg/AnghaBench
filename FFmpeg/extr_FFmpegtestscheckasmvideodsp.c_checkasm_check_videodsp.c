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
struct TYPE_3__ {int /*<<< orphan*/  emulated_edge_mc; } ;
typedef  TYPE_1__ VideoDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  check_emu_edge (int /*<<< orphan*/ ) ; 
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_videodsp_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  uint8_t ; 

void checkasm_check_videodsp(void)
{
    VideoDSPContext vdsp;

    ff_videodsp_init(&vdsp, 8);
    if (check_func(vdsp.emulated_edge_mc, "emulated_edge_mc_8"))
        check_emu_edge(uint8_t);

    report("emulated_edge_mc");
}