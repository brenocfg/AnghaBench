#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int supported_out_devices; int model; int outmask; int /*<<< orphan*/  submodel; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
#define  MDL_SB16 128 
 int /*<<< orphan*/  SB16_OMASK ; 
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  SUBMDL_ALS007 ; 
 unsigned char* sb16_recmasks_L ; 
 unsigned char* sb16_recmasks_R ; 
 int /*<<< orphan*/  sb_setmixer (TYPE_1__*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int set_outmask(sb_devc * devc, int mask)
{
	int devmask, i;
	unsigned char  regimage;

	devmask = mask & devc->supported_out_devices;

	switch (devc->model)
	{
		case MDL_SB16:
			if (devc->submodel == SUBMDL_ALS007) 
				break;
			else
			{
				regimage = 0;
				for (i = 0; i < SOUND_MIXER_NRDEVICES; i++)
				{
					if ((1 << i) & devmask)
					{
						regimage |= (sb16_recmasks_L[i] | sb16_recmasks_R[i]);
					}
					sb_setmixer (devc, SB16_OMASK, regimage);
				}
			}
			break;
		default:
			break;
	}

	devc->outmask = devmask;
	return devc->outmask;
}