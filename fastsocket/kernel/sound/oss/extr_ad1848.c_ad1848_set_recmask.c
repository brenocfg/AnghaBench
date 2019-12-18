#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int supported_rec_devices; int* mixer_reroute; int recmask; int /*<<< orphan*/  lock; TYPE_1__** mix_devices; } ;
typedef  TYPE_2__ ad1848_info ;
struct TYPE_6__ {scalar_t__ nbits; int recpol; int recreg; int recpos; } ;

/* Variables and functions */
 int LEFT_CHN ; 
 int RIGHT_CHN ; 
#define  SOUND_MASK_CD 133 
#define  SOUND_MASK_IMIX 132 
#define  SOUND_MASK_LINE 131 
#define  SOUND_MASK_LINE1 130 
#define  SOUND_MASK_LINE3 129 
#define  SOUND_MASK_MIC 128 
 int ad_read (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ad_write (TYPE_2__*,int,unsigned char) ; 
 int /*<<< orphan*/  soundpro ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ad1848_set_recmask(ad1848_info * devc, int mask)
{
	unsigned char   recdev;
	int             i, n;
	unsigned long flags;

	mask &= devc->supported_rec_devices;

	/* Rename the mixer bits if necessary */
	for (i = 0; i < 32; i++)
	{
		if (devc->mixer_reroute[i] != i)
		{
			if (mask & (1 << i))
			{
				mask &= ~(1 << i);
				mask |= (1 << devc->mixer_reroute[i]);
			}
		}
	}
	
	n = 0;
	for (i = 0; i < 32; i++)	/* Count selected device bits */
		if (mask & (1 << i))
			n++;

	spin_lock_irqsave(&devc->lock,flags);
	if (!soundpro) {
		if (n == 0)
			mask = SOUND_MASK_MIC;
		else if (n != 1) {	/* Too many devices selected */
			mask &= ~devc->recmask;	/* Filter out active settings */

			n = 0;
			for (i = 0; i < 32; i++)	/* Count selected device bits */
				if (mask & (1 << i))
					n++;

			if (n != 1)
				mask = SOUND_MASK_MIC;
		}
		switch (mask) {
		case SOUND_MASK_MIC:
			recdev = 2;
			break;

		case SOUND_MASK_LINE:
		case SOUND_MASK_LINE3:
			recdev = 0;
			break;

		case SOUND_MASK_CD:
		case SOUND_MASK_LINE1:
			recdev = 1;
			break;

		case SOUND_MASK_IMIX:
			recdev = 3;
			break;

		default:
			mask = SOUND_MASK_MIC;
			recdev = 2;
		}

		recdev <<= 6;
		ad_write(devc, 0, (ad_read(devc, 0) & 0x3f) | recdev);
		ad_write(devc, 1, (ad_read(devc, 1) & 0x3f) | recdev);
	} else { /* soundpro */
		unsigned char val;
		int set_rec_bit;
		int j;

		for (i = 0; i < 32; i++) {	/* For each bit */
			if ((devc->supported_rec_devices & (1 << i)) == 0)
				continue;	/* Device not supported */

			for (j = LEFT_CHN; j <= RIGHT_CHN; j++) {
				if (devc->mix_devices[i][j].nbits == 0) /* Inexistent channel */
					continue;

				/*
				 * This is tricky:
				 * set_rec_bit becomes 1 if the corresponding bit in mask is set
				 * then it gets flipped if the polarity is inverse
				 */
				set_rec_bit = ((mask & (1 << i)) != 0) ^ devc->mix_devices[i][j].recpol;

				val = ad_read(devc, devc->mix_devices[i][j].recreg);
				val &= ~(1 << devc->mix_devices[i][j].recpos);
				val |= (set_rec_bit << devc->mix_devices[i][j].recpos);
				ad_write(devc, devc->mix_devices[i][j].recreg, val);
			}
		}
	}
	spin_unlock_irqrestore(&devc->lock,flags);

	/* Rename the mixer bits back if necessary */
	for (i = 0; i < 32; i++)
	{
		if (devc->mixer_reroute[i] != i)
		{
			if (mask & (1 << devc->mixer_reroute[i]))
			{
				mask &= ~(1 << devc->mixer_reroute[i]);
				mask |= (1 << i);
			}
		}
	}
	devc->recmask = mask;
	return mask;
}