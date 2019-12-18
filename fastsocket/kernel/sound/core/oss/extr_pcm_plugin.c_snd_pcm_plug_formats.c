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
typedef  int u64 ;
typedef  int u32 ;
struct snd_mask {int* bits; } ;

/* Variables and functions */
 int SNDRV_PCM_FMTBIT_S16_BE ; 
 int SNDRV_PCM_FMTBIT_S16_LE ; 
 int SNDRV_PCM_FMTBIT_S24_3BE ; 
 int SNDRV_PCM_FMTBIT_S24_3LE ; 
 int SNDRV_PCM_FMTBIT_S24_BE ; 
 int SNDRV_PCM_FMTBIT_S24_LE ; 
 int SNDRV_PCM_FMTBIT_S32_BE ; 
 int SNDRV_PCM_FMTBIT_S32_LE ; 
 int SNDRV_PCM_FMTBIT_S8 ; 
 int SNDRV_PCM_FMTBIT_U16_BE ; 
 int SNDRV_PCM_FMTBIT_U16_LE ; 
 int SNDRV_PCM_FMTBIT_U24_3BE ; 
 int SNDRV_PCM_FMTBIT_U24_3LE ; 
 int SNDRV_PCM_FMTBIT_U24_BE ; 
 int SNDRV_PCM_FMTBIT_U24_LE ; 
 int SNDRV_PCM_FMTBIT_U32_BE ; 
 int SNDRV_PCM_FMTBIT_U32_LE ; 
 int SNDRV_PCM_FMTBIT_U8 ; 
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_MU_LAW ; 
 int /*<<< orphan*/  snd_mask_set (struct snd_mask*,int /*<<< orphan*/ ) ; 
 int snd_mask_test (struct snd_mask*,int) ; 

__attribute__((used)) static int snd_pcm_plug_formats(struct snd_mask *mask, int format)
{
	struct snd_mask formats = *mask;
	u64 linfmts = (SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8 |
		       SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_S16_LE |
		       SNDRV_PCM_FMTBIT_U16_BE | SNDRV_PCM_FMTBIT_S16_BE |
		       SNDRV_PCM_FMTBIT_U24_LE | SNDRV_PCM_FMTBIT_S24_LE |
		       SNDRV_PCM_FMTBIT_U24_BE | SNDRV_PCM_FMTBIT_S24_BE |
		       SNDRV_PCM_FMTBIT_U24_3LE | SNDRV_PCM_FMTBIT_S24_3LE |
		       SNDRV_PCM_FMTBIT_U24_3BE | SNDRV_PCM_FMTBIT_S24_3BE |
		       SNDRV_PCM_FMTBIT_U32_LE | SNDRV_PCM_FMTBIT_S32_LE |
		       SNDRV_PCM_FMTBIT_U32_BE | SNDRV_PCM_FMTBIT_S32_BE);
	snd_mask_set(&formats, SNDRV_PCM_FORMAT_MU_LAW);
	
	if (formats.bits[0] & (u32)linfmts)
		formats.bits[0] |= (u32)linfmts;
	if (formats.bits[1] & (u32)(linfmts >> 32))
		formats.bits[1] |= (u32)(linfmts >> 32);
	return snd_mask_test(&formats, format);
}