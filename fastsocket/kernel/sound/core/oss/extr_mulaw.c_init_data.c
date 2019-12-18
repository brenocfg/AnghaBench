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
struct mulaw_priv {int cvt_endian; int flip; int native_bytes; int copy_bytes; int native_ofs; int copy_ofs; } ;

/* Variables and functions */
 scalar_t__ snd_pcm_format_big_endian (int) ; 
 scalar_t__ snd_pcm_format_little_endian (int) ; 
 int snd_pcm_format_physical_width (int) ; 
 int /*<<< orphan*/  snd_pcm_format_signed (int) ; 
 int snd_pcm_format_width (int) ; 

__attribute__((used)) static void init_data(struct mulaw_priv *data, int format)
{
#ifdef SNDRV_LITTLE_ENDIAN
	data->cvt_endian = snd_pcm_format_big_endian(format) > 0;
#else
	data->cvt_endian = snd_pcm_format_little_endian(format) > 0;
#endif
	if (!snd_pcm_format_signed(format))
		data->flip = 0x8000;
	data->native_bytes = snd_pcm_format_physical_width(format) / 8;
	data->copy_bytes = data->native_bytes < 2 ? 1 : 2;
	if (snd_pcm_format_little_endian(format)) {
		data->native_ofs = data->native_bytes - data->copy_bytes;
		data->copy_ofs = 2 - data->copy_bytes;
	} else {
		/* S24 in 4bytes need an 1 byte offset */
		data->native_ofs = data->native_bytes -
			snd_pcm_format_width(format) / 8;
	}
}