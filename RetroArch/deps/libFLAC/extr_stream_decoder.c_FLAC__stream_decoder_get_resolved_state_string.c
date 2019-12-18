#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* protected_; } ;
struct TYPE_4__ {size_t state; } ;
typedef  TYPE_2__ FLAC__StreamDecoder ;

/* Variables and functions */
 char const** FLAC__StreamDecoderStateString ; 

const char *FLAC__stream_decoder_get_resolved_state_string(const FLAC__StreamDecoder *decoder)
{
	return FLAC__StreamDecoderStateString[decoder->protected_->state];
}