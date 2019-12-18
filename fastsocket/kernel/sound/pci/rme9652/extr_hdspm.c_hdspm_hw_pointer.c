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
struct hdspm {int period_bytes; int /*<<< orphan*/  precise_ptr; } ;
typedef  int snd_pcm_uframes_t ;

/* Variables and functions */
 int HDSPM_BufferID ; 
 int HDSPM_BufferPositionMask ; 
 int /*<<< orphan*/  HDSPM_statusRegister ; 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t hdspm_hw_pointer(struct hdspm * hdspm)
{
	int position;

	position = hdspm_read(hdspm, HDSPM_statusRegister);

	if (!hdspm->precise_ptr)
		return (position & HDSPM_BufferID) ?
			(hdspm->period_bytes / 4) : 0;

	/* hwpointer comes in bytes and is 64Bytes accurate (by docu since
	   PCI Burst)
	   i have experimented that it is at most 64 Byte to much for playing 
	   so substraction of 64 byte should be ok for ALSA, but use it only
	   for application where you know what you do since if you come to
	   near with record pointer it can be a disaster */

	position &= HDSPM_BufferPositionMask;
	position = ((position - 64) % (2 * hdspm->period_bytes)) / 4;

	return position;
}