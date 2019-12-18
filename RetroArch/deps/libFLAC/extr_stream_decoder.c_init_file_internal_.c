#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* protected_; } ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  initstate; } ;
typedef  int /*<<< orphan*/  FLAC__bool ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoderWriteCallback ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoderMetadataCallback ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoderInitStatus ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoderErrorCallback ;
typedef  TYPE_2__ FLAC__StreamDecoder ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_INIT_STATUS_ALREADY_INITIALIZED ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_INIT_STATUS_ERROR_OPENING_FILE ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_INIT_STATUS_INVALID_CALLBACKS ; 
 scalar_t__ FLAC__STREAM_DECODER_UNINITIALIZED ; 
 int /*<<< orphan*/ * flac_fopen (char const*,char*) ; 
 int /*<<< orphan*/  init_FILE_internal_ (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdin ; 

__attribute__((used)) static FLAC__StreamDecoderInitStatus init_file_internal_(
	FLAC__StreamDecoder *decoder,
	const char *filename,
	FLAC__StreamDecoderWriteCallback write_callback,
	FLAC__StreamDecoderMetadataCallback metadata_callback,
	FLAC__StreamDecoderErrorCallback error_callback,
	void *client_data,
	FLAC__bool is_ogg
)
{
	FILE *file;

	FLAC__ASSERT(0 != decoder);

	/*
	 * To make sure that our file does not go unclosed after an error, we
	 * have to do the same entrance checks here that are later performed
	 * in FLAC__stream_decoder_init_FILE() before the FILE* is assigned.
	 */
	if(decoder->protected_->state != FLAC__STREAM_DECODER_UNINITIALIZED)
		return decoder->protected_->initstate = FLAC__STREAM_DECODER_INIT_STATUS_ALREADY_INITIALIZED;

	if(0 == write_callback || 0 == error_callback)
		return decoder->protected_->initstate = FLAC__STREAM_DECODER_INIT_STATUS_INVALID_CALLBACKS;

	file = filename? flac_fopen(filename, "rb") : stdin;

	if(0 == file)
		return FLAC__STREAM_DECODER_INIT_STATUS_ERROR_OPENING_FILE;

	return init_FILE_internal_(decoder, file, write_callback, metadata_callback, error_callback, client_data, is_ogg);
}