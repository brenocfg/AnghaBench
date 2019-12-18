#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_12__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {TYPE_2__* codecpar; } ;
struct TYPE_8__ {int* data; int size; } ;
struct TYPE_10__ {TYPE_1__ codec_priv; TYPE_4__* stream; } ;
struct TYPE_9__ {int channel_layout; } ;
typedef  TYPE_3__ MatroskaTrack ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_5__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FLAC_METADATA_TYPE_VORBIS_COMMENT ; 
 int FLAC_STREAMINFO_SIZE ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_5__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_vorbis_comment (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flac_parse_block_header (int*,int*,int*,int*) ; 
 int strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int matroska_parse_flac(AVFormatContext *s,
                               MatroskaTrack *track,
                               int *offset)
{
    AVStream *st = track->stream;
    uint8_t *p = track->codec_priv.data;
    int size   = track->codec_priv.size;

    if (size < 8 + FLAC_STREAMINFO_SIZE || p[4] & 0x7f) {
        av_log(s, AV_LOG_WARNING, "Invalid FLAC private data\n");
        track->codec_priv.size = 0;
        return 0;
    }
    *offset = 8;
    track->codec_priv.size = 8 + FLAC_STREAMINFO_SIZE;

    p    += track->codec_priv.size;
    size -= track->codec_priv.size;

    /* parse the remaining metadata blocks if present */
    while (size >= 4) {
        int block_last, block_type, block_size;

        flac_parse_block_header(p, &block_last, &block_type, &block_size);

        p    += 4;
        size -= 4;
        if (block_size > size)
            return 0;

        /* check for the channel mask */
        if (block_type == FLAC_METADATA_TYPE_VORBIS_COMMENT) {
            AVDictionary *dict = NULL;
            AVDictionaryEntry *chmask;

            ff_vorbis_comment(s, &dict, p, block_size, 0);
            chmask = av_dict_get(dict, "WAVEFORMATEXTENSIBLE_CHANNEL_MASK", NULL, 0);
            if (chmask) {
                uint64_t mask = strtol(chmask->value, NULL, 0);
                if (!mask || mask & ~0x3ffffULL) {
                    av_log(s, AV_LOG_WARNING,
                           "Invalid value of WAVEFORMATEXTENSIBLE_CHANNEL_MASK\n");
                } else
                    st->codecpar->channel_layout = mask;
            }
            av_dict_free(&dict);
        }

        p    += block_size;
        size -= block_size;
    }

    return 0;
}