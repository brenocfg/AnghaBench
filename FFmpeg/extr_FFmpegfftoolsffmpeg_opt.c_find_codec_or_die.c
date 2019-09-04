#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_10__ {int type; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ AVCodecDescriptor ;
typedef  TYPE_2__ AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*,...) ; 
 TYPE_1__* avcodec_descriptor_get_by_name (char const*) ; 
 TYPE_2__* avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 TYPE_2__* avcodec_find_decoder_by_name (char const*) ; 
 TYPE_2__* avcodec_find_encoder (int /*<<< orphan*/ ) ; 
 TYPE_2__* avcodec_find_encoder_by_name (char const*) ; 
 int /*<<< orphan*/  exit_program (int) ; 

__attribute__((used)) static AVCodec *find_codec_or_die(const char *name, enum AVMediaType type, int encoder)
{
    const AVCodecDescriptor *desc;
    const char *codec_string = encoder ? "encoder" : "decoder";
    AVCodec *codec;

    codec = encoder ?
        avcodec_find_encoder_by_name(name) :
        avcodec_find_decoder_by_name(name);

    if (!codec && (desc = avcodec_descriptor_get_by_name(name))) {
        codec = encoder ? avcodec_find_encoder(desc->id) :
                          avcodec_find_decoder(desc->id);
        if (codec)
            av_log(NULL, AV_LOG_VERBOSE, "Matched %s '%s' for codec '%s'.\n",
                   codec_string, codec->name, desc->name);
    }

    if (!codec) {
        av_log(NULL, AV_LOG_FATAL, "Unknown %s '%s'\n", codec_string, name);
        exit_program(1);
    }
    if (codec->type != type) {
        av_log(NULL, AV_LOG_FATAL, "Invalid %s type '%s'\n", codec_string, name);
        exit_program(1);
    }
    return codec;
}