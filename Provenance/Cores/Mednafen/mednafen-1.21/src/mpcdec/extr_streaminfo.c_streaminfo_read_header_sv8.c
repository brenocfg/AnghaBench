#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int mpc_uint32_t ;
struct TYPE_8__ {int stream_version; double samples; double beg_silence; int is_true_gapless; double sample_freq; int max_band; int channels; int ms; int block_pwr; double average_bitrate; double tag_offset; double header_position; scalar_t__ bitrate; } ;
typedef  TYPE_1__ mpc_streaminfo ;
typedef  int /*<<< orphan*/  mpc_status ;
typedef  scalar_t__ mpc_size_t ;
struct TYPE_9__ {int count; scalar_t__ buff; } ;
typedef  TYPE_2__ mpc_bits_reader ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_STATUS_FAIL ; 
 int /*<<< orphan*/  check_streaminfo (TYPE_1__*) ; 
 int /*<<< orphan*/  mpc_bits_get_size (TYPE_2__*,double*) ; 
 int mpc_bits_read (TYPE_2__*,int) ; 
 int mpc_crc32 (scalar_t__,int) ; 
 double* samplefreqs ; 

mpc_status
streaminfo_read_header_sv8(mpc_streaminfo* si, const mpc_bits_reader * r_in,
						   mpc_size_t block_size)
{
	mpc_uint32_t CRC;
	mpc_bits_reader r = *r_in;

	CRC = (mpc_bits_read(&r, 16) << 16) | mpc_bits_read(&r, 16);
	if (CRC != mpc_crc32(r.buff + 1 - (r.count >> 3), (int)block_size - 4))
		return MPC_STATUS_FAIL;

	si->stream_version = mpc_bits_read(&r, 8);
	if (si->stream_version != 8)
		return MPC_STATUS_FAIL;

	mpc_bits_get_size(&r, &si->samples);
	mpc_bits_get_size(&r, &si->beg_silence);

	si->is_true_gapless = 1;
	si->sample_freq = samplefreqs[mpc_bits_read(&r, 3)];
	si->max_band = mpc_bits_read(&r, 5) + 1;
	si->channels = mpc_bits_read(&r, 4) + 1;
	si->ms = mpc_bits_read(&r, 1);
	si->block_pwr = mpc_bits_read(&r, 3) * 2;

	si->bitrate = 0;

	if ((si->samples - si->beg_silence) != 0)
		si->average_bitrate = (si->tag_offset - si->header_position) * 8.0
				*  si->sample_freq / (si->samples - si->beg_silence);

	return check_streaminfo(si);
}