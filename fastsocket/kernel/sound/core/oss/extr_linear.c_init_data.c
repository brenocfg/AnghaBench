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
struct linear_priv {int dst_bytes; int cvt_endian; int copy_bytes; int copy_ofs; int src_ofs; int dst_ofs; int /*<<< orphan*/  flip; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ snd_pcm_format_little_endian (int) ; 
 int snd_pcm_format_physical_width (int) ; 
 scalar_t__ snd_pcm_format_signed (int) ; 
 int snd_pcm_format_width (int) ; 

__attribute__((used)) static void init_data(struct linear_priv *data, int src_format, int dst_format)
{
	int src_le, dst_le, src_bytes, dst_bytes;

	src_bytes = snd_pcm_format_width(src_format) / 8;
	dst_bytes = snd_pcm_format_width(dst_format) / 8;
	src_le = snd_pcm_format_little_endian(src_format) > 0;
	dst_le = snd_pcm_format_little_endian(dst_format) > 0;

	data->dst_bytes = dst_bytes;
	data->cvt_endian = src_le != dst_le;
	data->copy_bytes = src_bytes < dst_bytes ? src_bytes : dst_bytes;
	if (src_le) {
		data->copy_ofs = 4 - data->copy_bytes;
		data->src_ofs = src_bytes - data->copy_bytes;
	} else
		data->src_ofs = snd_pcm_format_physical_width(src_format) / 8 -
			src_bytes;
	if (dst_le)
		data->dst_ofs = 4 - data->dst_bytes;
	else
		data->dst_ofs = snd_pcm_format_physical_width(dst_format) / 8 -
			dst_bytes;
	if (snd_pcm_format_signed(src_format) !=
	    snd_pcm_format_signed(dst_format)) {
		if (dst_le)
			data->flip = cpu_to_le32(0x80000000);
		else
			data->flip = cpu_to_be32(0x80000000);
	}
}