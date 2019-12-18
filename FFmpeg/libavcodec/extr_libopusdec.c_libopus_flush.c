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
struct libopus_context {int /*<<< orphan*/  pre_skip; int /*<<< orphan*/  dec; } ;
struct TYPE_5__ {TYPE_1__* internal; struct libopus_context* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  skip_samples; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  OPUS_RESET_STATE ; 
 int /*<<< orphan*/  opus_multistream_decoder_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void libopus_flush(AVCodecContext *avc)
{
    struct libopus_context *opus = avc->priv_data;

    opus_multistream_decoder_ctl(opus->dec, OPUS_RESET_STATE);
    /* The stream can have been extracted by a tool that is not Opus-aware.
       Therefore, any packet can become the first of the stream. */
    avc->internal->skip_samples = opus->pre_skip;
}