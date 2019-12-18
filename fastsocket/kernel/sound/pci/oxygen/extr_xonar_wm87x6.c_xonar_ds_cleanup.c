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
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8776_RESET ; 
 int /*<<< orphan*/  wm8776_write (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xonar_disable_output (struct oxygen*) ; 

__attribute__((used)) static void xonar_ds_cleanup(struct oxygen *chip)
{
	xonar_disable_output(chip);
	wm8776_write(chip, WM8776_RESET, 0);
}