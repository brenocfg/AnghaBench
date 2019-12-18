#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int mpc_uint64_t ;
typedef  int mpc_uint32_t ;
typedef  int /*<<< orphan*/  mpc_status ;
typedef  int mpc_seek_t ;
struct TYPE_15__ {int buff; } ;
struct TYPE_11__ {int block_pwr; int samples; int stream_version; scalar_t__ beg_silence; } ;
struct TYPE_12__ {int seek_pwr; int seek_table_size; int* seek_table; TYPE_7__* d; TYPE_8__ bits_reader; TYPE_1__ si; } ;
typedef  TYPE_2__ mpc_demux ;
struct TYPE_13__ {scalar_t__ size; int /*<<< orphan*/  key; } ;
typedef  TYPE_3__ mpc_block ;
struct TYPE_14__ {int decoded_samples; int samples_to_skip; } ;

/* Variables and functions */
 int MPC_DECODER_SYNTH_DELAY ; 
 int MPC_FRAME_LENGTH ; 
 int /*<<< orphan*/  MPC_STATUS_OK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int mpc_bits_get_block (TYPE_8__*,TYPE_3__*) ; 
 scalar_t__ mpc_bits_read (TYPE_8__*,int) ; 
 int /*<<< orphan*/  mpc_decoder_reset_scf (TYPE_7__*,int) ; 
 scalar_t__ mpc_demux_pos (TYPE_2__*) ; 
 int /*<<< orphan*/  mpc_demux_seek (TYPE_2__*,int,int) ; 

mpc_status mpc_demux_seek_sample(mpc_demux * d, mpc_uint64_t destsample)
{
	mpc_uint32_t fwd, samples_to_skip, i;
	mpc_uint32_t block_samples = MPC_FRAME_LENGTH << d->si.block_pwr;
	mpc_seek_t fpos;

	destsample += d->si.beg_silence;
	if (destsample > d->si.samples) destsample = d->si.samples;
	fwd = (mpc_uint32_t) (destsample / block_samples);
	samples_to_skip = MPC_DECODER_SYNTH_DELAY +
			(mpc_uint32_t) (destsample % block_samples);
	if (d->si.stream_version == 7) {
		if (fwd > 32) {
			fwd -= 32;
			samples_to_skip += MPC_FRAME_LENGTH * 32;
		} else {
			samples_to_skip += MPC_FRAME_LENGTH * fwd;
			fwd = 0;
		}
	}

	i = fwd >> (d->seek_pwr - d->si.block_pwr);
	if (i >= d->seek_table_size)
		i = d->seek_table_size - 1;
	fpos = d->seek_table[i];
	i <<= d->seek_pwr - d->si.block_pwr;
	d->d->decoded_samples = i * block_samples;

	if (d->si.stream_version >= 8) {
		mpc_block b;
		int size;
		mpc_demux_seek(d, fpos, 11);
		size = mpc_bits_get_block(&d->bits_reader, &b);
		while(i < fwd) {
			if (memcmp(b.key, "AP", 2) == 0) {
				if (d->d->decoded_samples == (d->seek_table_size << d->seek_pwr) * MPC_FRAME_LENGTH) {
					d->seek_table[d->seek_table_size] = (mpc_seek_t) mpc_demux_pos(d) - 8 * size;
					d->seek_table_size ++;
				}
				d->d->decoded_samples += block_samples;
				i++;
			}
			fpos += ((mpc_uint32_t)b.size + size) * 8;
			mpc_demux_seek(d, fpos, 11);
			size = mpc_bits_get_block(&d->bits_reader, &b);
		}
		d->bits_reader.buff -= size;
	} else {
		mpc_decoder_reset_scf(d->d, fwd != 0);
		mpc_demux_seek(d, fpos, 4);
		for( ; i < fwd; i++){
			if (d->d->decoded_samples == (d->seek_table_size << d->seek_pwr) * MPC_FRAME_LENGTH) {
				d->seek_table[d->seek_table_size] = (mpc_seek_t) mpc_demux_pos(d);
				d->seek_table_size ++;
			}
			d->d->decoded_samples += block_samples;
			fpos += mpc_bits_read(&d->bits_reader, 20) + 20;
			mpc_demux_seek(d, fpos, 4);
		}
	}
	d->d->samples_to_skip = samples_to_skip;
	return MPC_STATUS_OK;
}