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
 int /*<<< orphan*/  HDSPM_midiStatusOut0 ; 
 int /*<<< orphan*/  HDSPM_midiStatusOut1 ; 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int snd_hdspm_midi_output_possible (struct hdspm *hdspm, int id)
{
	int fifo_bytes_used;

	if (id)
		fifo_bytes_used = hdspm_read(hdspm, HDSPM_midiStatusOut1);
	else
		fifo_bytes_used = hdspm_read(hdspm, HDSPM_midiStatusOut0);
	fifo_bytes_used &= 0xff;

	if (fifo_bytes_used < 128)
		return  128 - fifo_bytes_used;
	else
		return 0;
}