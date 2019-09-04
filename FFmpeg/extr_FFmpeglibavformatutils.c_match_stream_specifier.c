#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_13__ {int codec_type; scalar_t__ codec_id; int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_12__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int nb_programs; TYPE_1__** programs; } ;
struct TYPE_10__ {int disposition; scalar_t__ index; int id; TYPE_5__* codecpar; int /*<<< orphan*/  metadata; } ;
struct TYPE_9__ {int id; int nb_stream_indexes; scalar_t__* stream_index; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVMEDIA_TYPE_ATTACHMENT ; 
#define  AVMEDIA_TYPE_AUDIO 130 
 int AVMEDIA_TYPE_DATA ; 
 int AVMEDIA_TYPE_SUBTITLE ; 
#define  AVMEDIA_TYPE_UNKNOWN 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int AV_DISPOSITION_ATTACHED_PIC ; 
 int /*<<< orphan*/  AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_strdup (char const*) ; 
 char* av_strndup (char const*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_stream_specifier(AVFormatContext *s, AVStream *st,
                                  const char *spec, const char **indexptr)
{
    int match = 1;                      /* Stores if the specifier matches so far. */
    while (*spec) {
        if (*spec <= '9' && *spec >= '0') { /* opt:index */
            if (indexptr)
                *indexptr = spec;
            return match;
        } else if (*spec == 'v' || *spec == 'a' || *spec == 's' || *spec == 'd' ||
                   *spec == 't' || *spec == 'V') { /* opt:[vasdtV] */
            enum AVMediaType type;
            int nopic = 0;

            switch (*spec++) {
            case 'v': type = AVMEDIA_TYPE_VIDEO;      break;
            case 'a': type = AVMEDIA_TYPE_AUDIO;      break;
            case 's': type = AVMEDIA_TYPE_SUBTITLE;   break;
            case 'd': type = AVMEDIA_TYPE_DATA;       break;
            case 't': type = AVMEDIA_TYPE_ATTACHMENT; break;
            case 'V': type = AVMEDIA_TYPE_VIDEO; nopic = 1; break;
            default:  av_assert0(0);
            }
            if (*spec && *spec++ != ':')         /* If we are not at the end, then another specifier must follow. */
                return AVERROR(EINVAL);

#if FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
            if (type != st->codecpar->codec_type
               && (st->codecpar->codec_type != AVMEDIA_TYPE_UNKNOWN || st->codec->codec_type != type))
                match = 0;
    FF_ENABLE_DEPRECATION_WARNINGS
#else
            if (type != st->codecpar->codec_type)
                match = 0;
#endif
            if (nopic && (st->disposition & AV_DISPOSITION_ATTACHED_PIC))
                match = 0;
        } else if (*spec == 'p' && *(spec + 1) == ':') {
            int prog_id, i, j;
            int found = 0;
            char *endptr;
            spec += 2;
            prog_id = strtol(spec, &endptr, 0);
            /* Disallow empty id and make sure that if we are not at the end, then another specifier must follow. */
            if (spec == endptr || (*endptr && *endptr++ != ':'))
                return AVERROR(EINVAL);
            spec = endptr;
            if (match) {
                for (i = 0; i < s->nb_programs; i++) {
                    if (s->programs[i]->id != prog_id)
                        continue;

                    for (j = 0; j < s->programs[i]->nb_stream_indexes; j++) {
                        if (st->index == s->programs[i]->stream_index[j]) {
                            found = 1;
                            i = s->nb_programs;
                            break;
                        }
                    }
                }
            }
            if (!found)
                match = 0;
        } else if (*spec == '#' ||
                   (*spec == 'i' && *(spec + 1) == ':')) {
            int stream_id;
            char *endptr;
            spec += 1 + (*spec == 'i');
            stream_id = strtol(spec, &endptr, 0);
            if (spec == endptr || *endptr)                /* Disallow empty id and make sure we are at the end. */
                return AVERROR(EINVAL);
            return match && (stream_id == st->id);
        } else if (*spec == 'm' && *(spec + 1) == ':') {
            AVDictionaryEntry *tag;
            char *key, *val;
            int ret;

            if (match) {
               spec += 2;
               val = strchr(spec, ':');

               key = val ? av_strndup(spec, val - spec) : av_strdup(spec);
               if (!key)
                   return AVERROR(ENOMEM);

               tag = av_dict_get(st->metadata, key, NULL, 0);
               if (tag) {
                   if (!val || !strcmp(tag->value, val + 1))
                       ret = 1;
                   else
                       ret = 0;
               } else
                   ret = 0;

               av_freep(&key);
            }
            return match && ret;
        } else if (*spec == 'u' && *(spec + 1) == '\0') {
            AVCodecParameters *par = st->codecpar;
#if FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
            AVCodecContext *codec = st->codec;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            int val;
            switch (par->codec_type) {
            case AVMEDIA_TYPE_AUDIO:
                val = par->sample_rate && par->channels;
#if FF_API_LAVF_AVCTX
                val = val || (codec->sample_rate && codec->channels);
#endif
                if (par->format == AV_SAMPLE_FMT_NONE
#if FF_API_LAVF_AVCTX
                    && codec->sample_fmt == AV_SAMPLE_FMT_NONE
#endif
                    )
                    return 0;
                break;
            case AVMEDIA_TYPE_VIDEO:
                val = par->width && par->height;
#if FF_API_LAVF_AVCTX
                val = val || (codec->width && codec->height);
#endif
                if (par->format == AV_PIX_FMT_NONE
#if FF_API_LAVF_AVCTX
                    && codec->pix_fmt == AV_PIX_FMT_NONE
#endif
                    )
                    return 0;
                break;
            case AVMEDIA_TYPE_UNKNOWN:
                val = 0;
                break;
            default:
                val = 1;
                break;
            }
#if FF_API_LAVF_AVCTX
            return match && ((par->codec_id != AV_CODEC_ID_NONE || codec->codec_id != AV_CODEC_ID_NONE) && val != 0);
#else
            return match && (par->codec_id != AV_CODEC_ID_NONE && val != 0);
#endif
        } else {
            return AVERROR(EINVAL);
        }
    }

    return match;
}