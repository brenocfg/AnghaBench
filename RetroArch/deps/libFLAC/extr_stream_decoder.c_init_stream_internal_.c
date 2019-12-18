#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ sse41; scalar_t__ sse2; scalar_t__ mmx; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_1__ ia32; scalar_t__ use_asm; } ;
struct TYPE_12__ {TYPE_3__* private_; TYPE_2__* protected_; } ;
struct TYPE_11__ {int has_stream_info; int cached; int is_seeking; int internal_reset_hack; int /*<<< orphan*/  do_md5_checking; scalar_t__ samples_decoded; scalar_t__ next_fixed_block_size; scalar_t__ fixed_block_size; void* client_data; scalar_t__ error_callback; int /*<<< orphan*/  metadata_callback; scalar_t__ write_callback; scalar_t__ eof_callback; scalar_t__ length_callback; scalar_t__ tell_callback; scalar_t__ seek_callback; scalar_t__ read_callback; int /*<<< orphan*/  input; TYPE_7__ cpuinfo; int /*<<< orphan*/  local_lpc_restore_signal_64bit; void* local_lpc_restore_signal_16bit; void* local_lpc_restore_signal; scalar_t__ is_ogg; } ;
struct TYPE_10__ {scalar_t__ state; int /*<<< orphan*/  md5_checking; int /*<<< orphan*/  initstate; int /*<<< orphan*/  ogg_decoder_aspect; } ;
typedef  scalar_t__ FLAC__bool ;
typedef  scalar_t__ FLAC__StreamDecoderWriteCallback ;
typedef  scalar_t__ FLAC__StreamDecoderTellCallback ;
typedef  scalar_t__ FLAC__StreamDecoderSeekCallback ;
typedef  scalar_t__ FLAC__StreamDecoderReadCallback ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoderMetadataCallback ;
typedef  scalar_t__ FLAC__StreamDecoderLengthCallback ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoderInitStatus ;
typedef  scalar_t__ FLAC__StreamDecoderErrorCallback ;
typedef  scalar_t__ FLAC__StreamDecoderEofCallback ;
typedef  TYPE_4__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 scalar_t__ FLAC__CPUINFO_TYPE_IA32 ; 
 scalar_t__ FLAC__CPUINFO_TYPE_X86_64 ; 
 scalar_t__ FLAC__HAS_OGG ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_INIT_STATUS_ALREADY_INITIALIZED ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_INIT_STATUS_ERROR_OPENING_FILE ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_INIT_STATUS_INVALID_CALLBACKS ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_INIT_STATUS_MEMORY_ALLOCATION_ERROR ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_INIT_STATUS_OK ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_INIT_STATUS_UNSUPPORTED_CONTAINER ; 
 scalar_t__ FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR ; 
 scalar_t__ FLAC__STREAM_DECODER_UNINITIALIZED ; 
 int /*<<< orphan*/  FLAC__bitreader_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  FLAC__cpu_info (TYPE_7__*) ; 
 void* FLAC__lpc_restore_signal ; 
 void* FLAC__lpc_restore_signal_16_intrin_sse2 ; 
 void* FLAC__lpc_restore_signal_asm_ia32 ; 
 void* FLAC__lpc_restore_signal_asm_ia32_mmx ; 
 int /*<<< orphan*/  FLAC__lpc_restore_signal_wide ; 
 int /*<<< orphan*/  FLAC__lpc_restore_signal_wide_asm_ia32 ; 
 int /*<<< orphan*/  FLAC__lpc_restore_signal_wide_intrin_sse41 ; 
 int /*<<< orphan*/  FLAC__ogg_decoder_aspect_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FLAC__stream_decoder_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  read_callback_ ; 

__attribute__((used)) static FLAC__StreamDecoderInitStatus init_stream_internal_(
	FLAC__StreamDecoder *decoder,
	FLAC__StreamDecoderReadCallback read_callback,
	FLAC__StreamDecoderSeekCallback seek_callback,
	FLAC__StreamDecoderTellCallback tell_callback,
	FLAC__StreamDecoderLengthCallback length_callback,
	FLAC__StreamDecoderEofCallback eof_callback,
	FLAC__StreamDecoderWriteCallback write_callback,
	FLAC__StreamDecoderMetadataCallback metadata_callback,
	FLAC__StreamDecoderErrorCallback error_callback,
	void *client_data,
	FLAC__bool is_ogg
)
{
	FLAC__ASSERT(0 != decoder);

	if(decoder->protected_->state != FLAC__STREAM_DECODER_UNINITIALIZED)
		return FLAC__STREAM_DECODER_INIT_STATUS_ALREADY_INITIALIZED;

	if(FLAC__HAS_OGG == 0 && is_ogg)
		return FLAC__STREAM_DECODER_INIT_STATUS_UNSUPPORTED_CONTAINER;

	if(
		0 == read_callback ||
		0 == write_callback ||
		0 == error_callback ||
		(seek_callback && (0 == tell_callback || 0 == length_callback || 0 == eof_callback))
	)
		return FLAC__STREAM_DECODER_INIT_STATUS_INVALID_CALLBACKS;

#if FLAC__HAS_OGG
	decoder->private_->is_ogg = is_ogg;
	if(is_ogg && !FLAC__ogg_decoder_aspect_init(&decoder->protected_->ogg_decoder_aspect))
		return decoder->protected_->initstate = FLAC__STREAM_DECODER_INIT_STATUS_ERROR_OPENING_FILE;
#endif

	/*
	 * get the CPU info and set the function pointers
	 */
	FLAC__cpu_info(&decoder->private_->cpuinfo);
	/* first default to the non-asm routines */
	decoder->private_->local_lpc_restore_signal = FLAC__lpc_restore_signal;
	decoder->private_->local_lpc_restore_signal_64bit = FLAC__lpc_restore_signal_wide;
	decoder->private_->local_lpc_restore_signal_16bit = FLAC__lpc_restore_signal;
	/* now override with asm where appropriate */
#ifndef FLAC__NO_ASM
	if(decoder->private_->cpuinfo.use_asm) {
#ifdef FLAC__CPU_IA32
		FLAC__ASSERT(decoder->private_->cpuinfo.type == FLAC__CPUINFO_TYPE_IA32);
#ifdef FLAC__HAS_NASM
		decoder->private_->local_lpc_restore_signal_64bit = FLAC__lpc_restore_signal_wide_asm_ia32; /* OPT_IA32: was really necessary for GCC < 4.9 */
		if(decoder->private_->cpuinfo.ia32.mmx) {
			decoder->private_->local_lpc_restore_signal = FLAC__lpc_restore_signal_asm_ia32;
			decoder->private_->local_lpc_restore_signal_16bit = FLAC__lpc_restore_signal_asm_ia32_mmx;
		}
		else {
			decoder->private_->local_lpc_restore_signal = FLAC__lpc_restore_signal_asm_ia32;
			decoder->private_->local_lpc_restore_signal_16bit = FLAC__lpc_restore_signal_asm_ia32;
		}
#endif
#if FLAC__HAS_X86INTRIN && ! defined FLAC__INTEGER_ONLY_LIBRARY
# if defined FLAC__SSE2_SUPPORTED && !defined FLAC__HAS_NASM /* OPT_SSE: not better than MMX asm */
		if(decoder->private_->cpuinfo.ia32.sse2) {
			decoder->private_->local_lpc_restore_signal_16bit = FLAC__lpc_restore_signal_16_intrin_sse2;
		}
# endif
# if defined FLAC__SSE4_1_SUPPORTED
		if(decoder->private_->cpuinfo.ia32.sse41) {
			decoder->private_->local_lpc_restore_signal_64bit = FLAC__lpc_restore_signal_wide_intrin_sse41;
		}
# endif
#endif
#elif defined FLAC__CPU_X86_64
		FLAC__ASSERT(decoder->private_->cpuinfo.type == FLAC__CPUINFO_TYPE_X86_64);
		/* No useful SSE optimizations yet */
#endif
	}
#endif

	/* from here on, errors are fatal */

	if(!FLAC__bitreader_init(decoder->private_->input, read_callback_, decoder)) {
		decoder->protected_->state = FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR;
		return FLAC__STREAM_DECODER_INIT_STATUS_MEMORY_ALLOCATION_ERROR;
	}

	decoder->private_->read_callback = read_callback;
	decoder->private_->seek_callback = seek_callback;
	decoder->private_->tell_callback = tell_callback;
	decoder->private_->length_callback = length_callback;
	decoder->private_->eof_callback = eof_callback;
	decoder->private_->write_callback = write_callback;
	decoder->private_->metadata_callback = metadata_callback;
	decoder->private_->error_callback = error_callback;
	decoder->private_->client_data = client_data;
	decoder->private_->fixed_block_size = decoder->private_->next_fixed_block_size = 0;
	decoder->private_->samples_decoded = 0;
	decoder->private_->has_stream_info = false;
	decoder->private_->cached = false;

	decoder->private_->do_md5_checking = decoder->protected_->md5_checking;
	decoder->private_->is_seeking = false;

	decoder->private_->internal_reset_hack = true; /* so the following reset does not try to rewind the input */
	if(!FLAC__stream_decoder_reset(decoder)) {
		/* above call sets the state for us */
		return FLAC__STREAM_DECODER_INIT_STATUS_MEMORY_ALLOCATION_ERROR;
	}

	return FLAC__STREAM_DECODER_INIT_STATUS_OK;
}