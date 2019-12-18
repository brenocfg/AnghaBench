#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct snd_msndmidi {int /*<<< orphan*/  input_lock; TYPE_1__* dev; int /*<<< orphan*/  substream_input; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int MIDQ; void* mappedbase; } ;

/* Variables and functions */
 int JQS_wHead ; 
 int JQS_wSize ; 
 int JQS_wTail ; 
 int MIDQ_DATA_BUFF ; 
 int /*<<< orphan*/  MSNDMIDI_MODE_BIT_INPUT_TRIGGER ; 
 int readw (int) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (int,int) ; 

void snd_msndmidi_input_read(void *mpuv)
{
	unsigned long flags;
	struct snd_msndmidi *mpu = mpuv;
	void *pwMIDQData = mpu->dev->mappedbase + MIDQ_DATA_BUFF;

	spin_lock_irqsave(&mpu->input_lock, flags);
	while (readw(mpu->dev->MIDQ + JQS_wTail) !=
	       readw(mpu->dev->MIDQ + JQS_wHead)) {
		u16 wTmp, val;
		val = readw(pwMIDQData + 2 * readw(mpu->dev->MIDQ + JQS_wHead));

			if (test_bit(MSNDMIDI_MODE_BIT_INPUT_TRIGGER,
				     &mpu->mode))
				snd_rawmidi_receive(mpu->substream_input,
						    (unsigned char *)&val, 1);

		wTmp = readw(mpu->dev->MIDQ + JQS_wHead) + 1;
		if (wTmp > readw(mpu->dev->MIDQ + JQS_wSize))
			writew(0,  mpu->dev->MIDQ + JQS_wHead);
		else
			writew(wTmp,  mpu->dev->MIDQ + JQS_wHead);
	}
	spin_unlock_irqrestore(&mpu->input_lock, flags);
}