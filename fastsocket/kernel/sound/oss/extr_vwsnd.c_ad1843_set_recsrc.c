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
 int /*<<< orphan*/  DBGP (char*) ; 
 int EINVAL ; 
#define  SOUND_MASK_CD 131 
#define  SOUND_MASK_LINE 130 
#define  SOUND_MASK_MIC 129 
#define  SOUND_MASK_PCM 128 
 int /*<<< orphan*/  ad1843_DAADL ; 
 int /*<<< orphan*/  ad1843_DAADR ; 
 int /*<<< orphan*/  ad1843_LSS ; 
 int /*<<< orphan*/  ad1843_RSS ; 
 int ad1843_read_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ad1843_set_resample_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ad1843_write_multi (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad1843_set_recsrc(lithium_t *lith, int newsrc)
{
	int bits;
	int oldbits;

	switch (newsrc) {
	case SOUND_MASK_PCM:
		bits = 6;
		break;

	case SOUND_MASK_MIC:
		bits = 1;
		break;

	case SOUND_MASK_LINE:
		bits = 2;
		break;

	case SOUND_MASK_CD:
		bits = 3;
		break;

	default:
		return -EINVAL;
	}
	oldbits = ad1843_read_bits(lith, &ad1843_LSS);
	if (newsrc == SOUND_MASK_PCM && oldbits != 6) {
		DBGP("enabling digital resample mode\n");
		ad1843_set_resample_mode(lith, 1);
		ad1843_write_multi(lith, 2,
				   &ad1843_DAADL, 2,
				   &ad1843_DAADR, 2);
	} else if (newsrc != SOUND_MASK_PCM && oldbits == 6) {
		DBGP("disabling digital resample mode\n");
		ad1843_set_resample_mode(lith, 0);
		ad1843_write_multi(lith, 2,
				   &ad1843_DAADL, 0,
				   &ad1843_DAADR, 0);
	}
	ad1843_write_multi(lith, 2, &ad1843_LSS, bits, &ad1843_RSS, bits);
	return newsrc;
}