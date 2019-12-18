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
typedef  int /*<<< orphan*/  multisound_dev_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  dsp_full_reset () ; 
 int msnd_send_dsp_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int chk_send_dsp_cmd(multisound_dev_t *dev, register BYTE cmd)
{
	if (msnd_send_dsp_cmd(dev, cmd) == 0)
		return 0;
	dsp_full_reset();
	return msnd_send_dsp_cmd(dev, cmd);
}