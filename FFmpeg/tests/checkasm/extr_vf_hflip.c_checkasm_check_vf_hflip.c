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

/* Variables and functions */
 int /*<<< orphan*/  check_hflip (int,char*) ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_vf_hflip(void)
{
    check_hflip(1, "byte");
    report("hflip_byte");

    check_hflip(2, "short");
    report("hflip_short");
}