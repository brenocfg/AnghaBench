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
struct vx_core {int dummy; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_vx_dsp_boot (struct vx_core*,struct firmware const*) ; 
 int snd_vx_dsp_load (struct vx_core*,struct firmware const*) ; 
 int snd_vx_load_boot_image (struct vx_core*,struct firmware const*) ; 
 int vx_check_magic (struct vx_core*) ; 
 int vxp_load_xilinx_binary (struct vx_core*,struct firmware const*) ; 

__attribute__((used)) static int vxp_load_dsp(struct vx_core *vx, int index, const struct firmware *fw)
{
	int err;

	switch (index) {
	case 0:
		/* xilinx boot */
		if ((err = vx_check_magic(vx)) < 0)
			return err;
		if ((err = snd_vx_load_boot_image(vx, fw)) < 0)
			return err;
		return 0;
	case 1:
		/* xilinx image */
		return vxp_load_xilinx_binary(vx, fw);
	case 2:
		/* DSP boot */
		return snd_vx_dsp_boot(vx, fw);
	case 3:
		/* DSP image */
		return snd_vx_dsp_load(vx, fw);
	default:
		snd_BUG();
		return -EINVAL;
	}
}