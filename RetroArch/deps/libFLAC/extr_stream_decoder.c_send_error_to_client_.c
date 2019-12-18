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
struct TYPE_6__ {TYPE_1__* private_; } ;
struct TYPE_5__ {int /*<<< orphan*/  unparseable_frame_count; int /*<<< orphan*/  client_data; int /*<<< orphan*/  (* error_callback ) (TYPE_2__ const*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  is_seeking; } ;
typedef  scalar_t__ FLAC__StreamDecoderErrorStatus ;
typedef  TYPE_2__ FLAC__StreamDecoder ;

/* Variables and functions */
 scalar_t__ FLAC__STREAM_DECODER_ERROR_STATUS_UNPARSEABLE_STREAM ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,scalar_t__,int /*<<< orphan*/ ) ; 

void send_error_to_client_(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status)
{
	if(!decoder->private_->is_seeking)
		decoder->private_->error_callback(decoder, status, decoder->private_->client_data);
	else if(status == FLAC__STREAM_DECODER_ERROR_STATUS_UNPARSEABLE_STREAM)
		decoder->private_->unparseable_frame_count++;
}