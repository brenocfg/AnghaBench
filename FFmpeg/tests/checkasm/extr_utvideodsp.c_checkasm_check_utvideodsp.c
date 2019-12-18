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
struct TYPE_3__ {int /*<<< orphan*/  restore_rgb_planes10; int /*<<< orphan*/  restore_rgb_planes; } ;
typedef  TYPE_1__ UTVideoDSPContext ;

/* Variables and functions */
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_restore_rgb_planes () ; 
 int /*<<< orphan*/  check_restore_rgb_planes10 () ; 
 int /*<<< orphan*/  ff_utvideodsp_init (TYPE_1__*) ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_utvideodsp(void)
{
    UTVideoDSPContext h;

    ff_utvideodsp_init(&h);

    if (check_func(h.restore_rgb_planes, "restore_rgb_planes"))
        check_restore_rgb_planes();

    report("restore_rgb_planes");

    if (check_func(h.restore_rgb_planes10, "restore_rgb_planes10"))
        check_restore_rgb_planes10();

    report("restore_rgb_planes10");
}