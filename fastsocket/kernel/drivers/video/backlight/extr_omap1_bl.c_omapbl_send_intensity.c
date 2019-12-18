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
 int /*<<< orphan*/  OMAP_PWL_ENABLE ; 
 int /*<<< orphan*/  omap_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inline omapbl_send_intensity(int intensity)
{
	omap_writeb(intensity, OMAP_PWL_ENABLE);
}