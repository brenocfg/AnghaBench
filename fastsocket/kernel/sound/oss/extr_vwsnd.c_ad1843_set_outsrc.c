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
typedef  int /*<<< orphan*/  lithium_t ;

/* Variables and functions */
 int EINVAL ; 
 int SOUND_MASK_CD ; 
 int SOUND_MASK_LINE ; 
 int SOUND_MASK_MIC ; 
 int SOUND_MASK_PCM ; 
 int /*<<< orphan*/  ad1843_LDA1GM ; 
 int /*<<< orphan*/  ad1843_LMCMM ; 
 int /*<<< orphan*/  ad1843_LX1MM ; 
 int /*<<< orphan*/  ad1843_LX2MM ; 
 int /*<<< orphan*/  ad1843_RDA1GM ; 
 int /*<<< orphan*/  ad1843_RMCMM ; 
 int /*<<< orphan*/  ad1843_RX1MM ; 
 int /*<<< orphan*/  ad1843_RX2MM ; 
 int /*<<< orphan*/  ad1843_write_multi (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad1843_set_outsrc(lithium_t *lith, int mask)
{
	int pcm, line, mic, cd;

	if (mask & ~(SOUND_MASK_PCM | SOUND_MASK_LINE |
		     SOUND_MASK_CD | SOUND_MASK_MIC))
		return -EINVAL;
	pcm  = (mask & SOUND_MASK_PCM)  ? 0 : 1;
	line = (mask & SOUND_MASK_LINE) ? 0 : 1;
	mic  = (mask & SOUND_MASK_MIC)  ? 0 : 1;
	cd   = (mask & SOUND_MASK_CD)   ? 0 : 1;

	ad1843_write_multi(lith, 2, &ad1843_LDA1GM, pcm, &ad1843_RDA1GM, pcm);
	ad1843_write_multi(lith, 2, &ad1843_LX1MM, line, &ad1843_RX1MM, line);
	ad1843_write_multi(lith, 2, &ad1843_LX2MM, cd,   &ad1843_RX2MM, cd);
	ad1843_write_multi(lith, 2, &ad1843_LMCMM, mic,  &ad1843_RMCMM, mic);

	return mask;
}