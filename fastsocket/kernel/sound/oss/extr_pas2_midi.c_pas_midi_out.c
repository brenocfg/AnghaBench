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

/* Variables and functions */
 scalar_t__ dump_to_midi (unsigned char) ; 
 int /*<<< orphan*/  pas_lock ; 
 size_t qhead ; 
 int qlen ; 
 size_t qtail ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char* tmp_queue ; 

__attribute__((used)) static int pas_midi_out(int dev, unsigned char midi_byte)
{

	unsigned long flags;

	/*
	 * Drain the local queue first
	 */

	spin_lock_irqsave(&pas_lock, flags);

	while (qlen && dump_to_midi(tmp_queue[qhead]))
	{
		qlen--;
		qhead++;
	}

	spin_unlock_irqrestore(&pas_lock, flags);

	/*
	 *	Output the byte if the local queue is empty.
	 */

	if (!qlen)
		if (dump_to_midi(midi_byte))
			return 1;

	/*
	 *	Put to the local queue
	 */

	if (qlen >= 256)
		return 0;	/* Local queue full */

	spin_lock_irqsave(&pas_lock, flags);

	tmp_queue[qtail] = midi_byte;
	qlen++;
	qtail++;

	spin_unlock_irqrestore(&pas_lock, flags);

	return 1;
}