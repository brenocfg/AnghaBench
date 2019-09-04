#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int extradata_size; void** extradata; } ;
struct TYPE_4__ {TYPE_3__* codecpar; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVStream ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (void***) ; 
 int /*<<< orphan*/ * av_mallocz (scalar_t__) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 scalar_t__ ff_alloc_extradata (TYPE_3__*,int) ; 
 int ff_hex_to_data (int /*<<< orphan*/ *,char const*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_fmtp_config(AVStream *st, const char *value)
{
    int len = ff_hex_to_data(NULL, value), i, ret = 0;
    GetBitContext gb;
    uint8_t *config;
    int audio_mux_version, same_time_framing, num_programs, num_layers;

    /* Pad this buffer, too, to avoid out of bounds reads with get_bits below */
    config = av_mallocz(len + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!config)
        return AVERROR(ENOMEM);
    ff_hex_to_data(config, value);
    init_get_bits(&gb, config, len*8);
    audio_mux_version = get_bits(&gb, 1);
    same_time_framing = get_bits(&gb, 1);
    skip_bits(&gb, 6); /* num_sub_frames */
    num_programs      = get_bits(&gb, 4);
    num_layers        = get_bits(&gb, 3);
    if (audio_mux_version != 0 || same_time_framing != 1 || num_programs != 0 ||
        num_layers != 0) {
        avpriv_report_missing_feature(NULL, "LATM config (%d,%d,%d,%d)",
                                      audio_mux_version, same_time_framing,
                                      num_programs, num_layers);
        ret = AVERROR_PATCHWELCOME;
        goto end;
    }
    av_freep(&st->codecpar->extradata);
    if (ff_alloc_extradata(st->codecpar, (get_bits_left(&gb) + 7)/8)) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    for (i = 0; i < st->codecpar->extradata_size; i++)
        st->codecpar->extradata[i] = get_bits(&gb, 8);

end:
    av_free(config);
    return ret;
}