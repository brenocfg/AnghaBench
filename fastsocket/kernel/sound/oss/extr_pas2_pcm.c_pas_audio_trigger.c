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
 int PCM_ENABLE_INPUT ; 
 int PCM_ENABLE_OUTPUT ; 
 int open_mode ; 
 int /*<<< orphan*/  pas_lock ; 
 int pas_read (int) ; 
 int /*<<< orphan*/  pas_write (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pas_audio_trigger(int dev, int state)
{
	unsigned long   flags;

	spin_lock_irqsave(&pas_lock, flags);
	state &= open_mode;

	if (state & PCM_ENABLE_OUTPUT)
		pas_write(pas_read(0xF8A) | 0x40 | 0x10, 0xF8A);
	else if (state & PCM_ENABLE_INPUT)
		pas_write((pas_read(0xF8A) | 0x40) & ~0x10, 0xF8A);
	else
		pas_write(pas_read(0xF8A) & ~0x40, 0xF8A);

	spin_unlock_irqrestore(&pas_lock, flags);
}