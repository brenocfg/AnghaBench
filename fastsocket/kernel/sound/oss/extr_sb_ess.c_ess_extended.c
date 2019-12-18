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
typedef  int /*<<< orphan*/  sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  sb_dsp_command (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ess_extended (sb_devc * devc)
{
	/* Enable extended mode */

	sb_dsp_command(devc, 0xc6);
}