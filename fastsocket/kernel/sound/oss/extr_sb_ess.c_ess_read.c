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
 int /*<<< orphan*/  sb_dsp_command (int /*<<< orphan*/ *,unsigned char) ; 
 int sb_dsp_get_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ess_read (sb_devc * devc, unsigned char reg)
{
	/* Read a byte from an extended mode register of ES1688 */

	/* Read register command */
	if (!sb_dsp_command(devc, 0xc0)) return -1;

	if (!sb_dsp_command(devc, reg )) return -1;

	return sb_dsp_get_byte(devc);
}