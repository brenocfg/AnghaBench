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
struct snd_info_buffer {int dummy; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_PCM ; 
 int /*<<< orphan*/  AC_PAR_STREAM ; 
 int /*<<< orphan*/  print_pcm_bits (struct snd_info_buffer*,unsigned int) ; 
 int /*<<< orphan*/  print_pcm_formats (struct snd_info_buffer*,unsigned int) ; 
 int /*<<< orphan*/  print_pcm_rates (struct snd_info_buffer*,unsigned int) ; 
 unsigned int snd_hda_param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*) ; 

__attribute__((used)) static void print_pcm_caps(struct snd_info_buffer *buffer,
			   struct hda_codec *codec, hda_nid_t nid)
{
	unsigned int pcm = snd_hda_param_read(codec, nid, AC_PAR_PCM);
	unsigned int stream = snd_hda_param_read(codec, nid, AC_PAR_STREAM);
	if (pcm == -1 || stream == -1) {
		snd_iprintf(buffer, "N/A\n");
		return;
	}
	print_pcm_rates(buffer, pcm);
	print_pcm_bits(buffer, pcm);
	print_pcm_formats(buffer, stream);
}