#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int supported_rec_devices; int model; int recmask; int /*<<< orphan*/  submodel; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 unsigned char ALS007_CD ; 
 unsigned char ALS007_LINE ; 
 unsigned char ALS007_MIC ; 
 int /*<<< orphan*/  ALS007_RECORD_SRC ; 
 unsigned char ALS007_SYNTH ; 
#define  MDL_ESS 136 
#define  MDL_JAZZ 135 
#define  MDL_SB16 134 
#define  MDL_SBPRO 133 
#define  MDL_SMW 132 
 int /*<<< orphan*/  SB16_IMASK_L ; 
 int /*<<< orphan*/  SB16_IMASK_R ; 
#define  SOUND_MASK_CD 131 
#define  SOUND_MASK_LINE 130 
#define  SOUND_MASK_MIC 129 
#define  SOUND_MASK_SYNTH 128 
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  SRC__CD ; 
 int /*<<< orphan*/  SRC__LINE ; 
 int /*<<< orphan*/  SRC__MIC ; 
 int /*<<< orphan*/  SUBMDL_ALS007 ; 
 int /*<<< orphan*/  ess_set_recmask (TYPE_1__*,int*) ; 
 unsigned char* sb16_recmasks_L ; 
 unsigned char* sb16_recmasks_R ; 
 int /*<<< orphan*/  sb_setmixer (TYPE_1__*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  set_recsrc (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_recmask(sb_devc * devc, int mask)
{
	int devmask, i;
	unsigned char  regimageL, regimageR;

	devmask = mask & devc->supported_rec_devices;

	switch (devc->model)
	{
		case MDL_SBPRO:
		case MDL_ESS:
		case MDL_JAZZ:
		case MDL_SMW:
			if (devc->model == MDL_ESS && ess_set_recmask (devc, &devmask)) {
				break;
			};
			if (devmask != SOUND_MASK_MIC &&
				devmask != SOUND_MASK_LINE &&
				devmask != SOUND_MASK_CD)
			{
				/*
				 * More than one device selected. Drop the
				 * previous selection
				 */
				devmask &= ~devc->recmask;
			}
			if (devmask != SOUND_MASK_MIC &&
				devmask != SOUND_MASK_LINE &&
				devmask != SOUND_MASK_CD)
			{
				/*
				 * More than one device selected. Default to
				 * mic
				 */
				devmask = SOUND_MASK_MIC;
			}
			if (devmask ^ devc->recmask)	/*
							 *	Input source changed
							 */
			{
				switch (devmask)
				{
					case SOUND_MASK_MIC:
						set_recsrc(devc, SRC__MIC);
						break;

					case SOUND_MASK_LINE:
						set_recsrc(devc, SRC__LINE);
						break;

					case SOUND_MASK_CD:
						set_recsrc(devc, SRC__CD);
						break;

					default:
						set_recsrc(devc, SRC__MIC);
				}
			}
			break;

		case MDL_SB16:
			if (!devmask)
				devmask = SOUND_MASK_MIC;

			if (devc->submodel == SUBMDL_ALS007) 
			{
				switch (devmask) 
				{
					case SOUND_MASK_LINE:
						sb_setmixer(devc, ALS007_RECORD_SRC, ALS007_LINE);
						break;
					case SOUND_MASK_CD:
						sb_setmixer(devc, ALS007_RECORD_SRC, ALS007_CD);
						break;
					case SOUND_MASK_SYNTH:
						sb_setmixer(devc, ALS007_RECORD_SRC, ALS007_SYNTH);
						break;
					default:           /* Also takes care of SOUND_MASK_MIC case */
						sb_setmixer(devc, ALS007_RECORD_SRC, ALS007_MIC);
						break;
				}
			}
			else
			{
				regimageL = regimageR = 0;
				for (i = 0; i < SOUND_MIXER_NRDEVICES; i++)
				{
					if ((1 << i) & devmask)
					{
						regimageL |= sb16_recmasks_L[i];
						regimageR |= sb16_recmasks_R[i];
					}
					sb_setmixer (devc, SB16_IMASK_L, regimageL);
					sb_setmixer (devc, SB16_IMASK_R, regimageR);
				}
			}
			break;
	}
	devc->recmask = devmask;
	return devc->recmask;
}