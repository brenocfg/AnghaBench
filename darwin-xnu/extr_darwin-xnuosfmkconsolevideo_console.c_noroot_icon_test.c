#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  PE_display_icon (int /*<<< orphan*/ ,char*) ; 
 int vc_progress_enable ; 

void noroot_icon_test(void) {
    boolean_t o_vc_progress_enable = vc_progress_enable;

    vc_progress_enable = 1;

    PE_display_icon( 0, "noroot");

    vc_progress_enable = o_vc_progress_enable;
}