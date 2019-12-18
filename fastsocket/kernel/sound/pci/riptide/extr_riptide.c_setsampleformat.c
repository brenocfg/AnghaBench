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
struct cmdif {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ SEND_SETF (struct cmdif*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 scalar_t__ snd_pcm_format_big_endian (unsigned char) ; 
 scalar_t__ snd_pcm_format_unsigned (unsigned char) ; 
 int snd_pcm_format_width (unsigned char) ; 
 int /*<<< orphan*/  snd_printdd (char*,...) ; 

__attribute__((used)) static int
setsampleformat(struct cmdif *cif,
		unsigned char mixer, unsigned char id,
		unsigned char channels, unsigned char format)
{
	unsigned char w, ch, sig, order;

	snd_printdd
	    ("setsampleformat mixer: %d id: %d channels: %d format: %d\n",
	     mixer, id, channels, format);
	ch = channels == 1;
	w = snd_pcm_format_width(format) == 8;
	sig = snd_pcm_format_unsigned(format) != 0;
	order = snd_pcm_format_big_endian(format) != 0;

	if (SEND_SETF(cif, mixer, w, ch, order, sig, id) &&
	    SEND_SETF(cif, mixer, w, ch, order, sig, id)) {
		snd_printdd("setsampleformat failed\n");
		return -EIO;
	}
	return 0;
}