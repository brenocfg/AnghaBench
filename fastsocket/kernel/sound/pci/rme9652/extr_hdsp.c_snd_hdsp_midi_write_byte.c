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
struct hdsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSP_midiDataOut0 ; 
 int /*<<< orphan*/  HDSP_midiDataOut1 ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_hdsp_midi_write_byte (struct hdsp *hdsp, int id, int val)
{
	/* the hardware already does the relevant bit-mask with 0xff */
	if (id)
		hdsp_write(hdsp, HDSP_midiDataOut1, val);
	else
		hdsp_write(hdsp, HDSP_midiDataOut0, val);
}