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
struct hdspm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_midiDataIn0 ; 
 int /*<<< orphan*/  HDSPM_midiDataIn1 ; 
 unsigned char hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned char snd_hdspm_midi_read_byte (struct hdspm *hdspm,
						      int id)
{
	/* the hardware already does the relevant bit-mask with 0xff */
	if (id)
		return hdspm_read(hdspm, HDSPM_midiDataIn1);
	else
		return hdspm_read(hdspm, HDSPM_midiDataIn0);
}