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
 int SOUND_MASK_CD ; 
 int SOUND_MASK_LINE ; 
 int SOUND_MASK_MIC ; 
 int SOUND_MASK_PCM ; 
 int /*<<< orphan*/  ad1843_LDA1GM ; 
 int /*<<< orphan*/  ad1843_LMCMM ; 
 int /*<<< orphan*/  ad1843_LX1MM ; 
 int /*<<< orphan*/  ad1843_LX2MM ; 
 scalar_t__ ad1843_read_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad1843_get_outsrc(lithium_t *lith)
{
	int pcm, line, mic, cd;

	pcm  = ad1843_read_bits(lith, &ad1843_LDA1GM) ? 0 : SOUND_MASK_PCM;
	line = ad1843_read_bits(lith, &ad1843_LX1MM)  ? 0 : SOUND_MASK_LINE;
	cd   = ad1843_read_bits(lith, &ad1843_LX2MM)  ? 0 : SOUND_MASK_CD;
	mic  = ad1843_read_bits(lith, &ad1843_LMCMM)  ? 0 : SOUND_MASK_MIC;

	return pcm | line | cd | mic;
}