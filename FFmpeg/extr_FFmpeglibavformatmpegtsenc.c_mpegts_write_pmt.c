#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_20__ {char* value; } ;
struct TYPE_19__ {int nb_streams; int /*<<< orphan*/  strict_std_compliance; scalar_t__ nb_programs; TYPE_5__** streams; TYPE_3__* priv_data; } ;
struct TYPE_18__ {int nb_stream_indexes; int* stream_index; } ;
struct TYPE_17__ {int disposition; TYPE_1__* codecpar; int /*<<< orphan*/  metadata; TYPE_2__* priv_data; } ;
struct TYPE_16__ {int pcr_pid; int /*<<< orphan*/  sid; int /*<<< orphan*/  pmt; TYPE_6__* program; } ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  tables_version; } ;
struct TYPE_14__ {int pid; } ;
struct TYPE_13__ {int codec_id; int sample_rate; int codec_type; int* extradata; int extradata_size; int channels; } ;
typedef  TYPE_2__ MpegTSWriteStream ;
typedef  TYPE_3__ MpegTSWrite ;
typedef  TYPE_4__ MpegTSService ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVProgram ;
typedef  TYPE_7__ AVFormatContext ;
typedef  TYPE_8__ AVDictionaryEntry ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 149 
#define  AVMEDIA_TYPE_DATA 148 
#define  AVMEDIA_TYPE_SUBTITLE 147 
#define  AVMEDIA_TYPE_VIDEO 146 
#define  AV_CODEC_ID_AAC 145 
#define  AV_CODEC_ID_AAC_LATM 144 
#define  AV_CODEC_ID_AC3 143 
#define  AV_CODEC_ID_CAVS 142 
#define  AV_CODEC_ID_DIRAC 141 
#define  AV_CODEC_ID_DTS 140 
 int const AV_CODEC_ID_DVB_SUBTITLE ; 
 int const AV_CODEC_ID_DVB_TELETEXT ; 
#define  AV_CODEC_ID_EAC3 139 
#define  AV_CODEC_ID_H264 138 
#define  AV_CODEC_ID_HEVC 137 
#define  AV_CODEC_ID_MP2 136 
#define  AV_CODEC_ID_MP3 135 
#define  AV_CODEC_ID_MPEG1VIDEO 134 
#define  AV_CODEC_ID_MPEG2VIDEO 133 
#define  AV_CODEC_ID_MPEG4 132 
#define  AV_CODEC_ID_OPUS 131 
 int const AV_CODEC_ID_S302M ; 
 int const AV_CODEC_ID_SMPTE_KLV ; 
#define  AV_CODEC_ID_TIMED_ID3 130 
#define  AV_CODEC_ID_TRUEHD 129 
#define  AV_CODEC_ID_VC1 128 
 int AV_DISPOSITION_CLEAN_EFFECTS ; 
 int AV_DISPOSITION_HEARING_IMPAIRED ; 
 int AV_DISPOSITION_VISUAL_IMPAIRED ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  FF_COMPLIANCE_NORMAL ; 
 int /*<<< orphan*/  MKTAG (char,char,char,char) ; 
 int MPEGTS_FLAG_AAC_LATM ; 
 int MPEGTS_FLAG_SYSTEM_B ; 
 int /*<<< orphan*/  PMT_TID ; 
 int SECTION_LENGTH ; 
 int STREAM_TYPE_AUDIO_AAC ; 
 int STREAM_TYPE_AUDIO_AAC_LATM ; 
 int STREAM_TYPE_AUDIO_AC3 ; 
 int STREAM_TYPE_AUDIO_DTS ; 
 int STREAM_TYPE_AUDIO_EAC3 ; 
 int STREAM_TYPE_AUDIO_MPEG1 ; 
 int STREAM_TYPE_AUDIO_MPEG2 ; 
 int STREAM_TYPE_AUDIO_TRUEHD ; 
 int STREAM_TYPE_METADATA ; 
 int STREAM_TYPE_PRIVATE_DATA ; 
 int STREAM_TYPE_VIDEO_CAVS ; 
 int STREAM_TYPE_VIDEO_DIRAC ; 
 int STREAM_TYPE_VIDEO_H264 ; 
 int STREAM_TYPE_VIDEO_HEVC ; 
 int STREAM_TYPE_VIDEO_MPEG2 ; 
 int STREAM_TYPE_VIDEO_MPEG4 ; 
 int STREAM_TYPE_VIDEO_VC1 ; 
 TYPE_8__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcmp (int const*,int const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  mpegts_write_section1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  put16 (int**,int) ; 
 int /*<<< orphan*/  put_registration_descriptor (int**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putbuf (int**,char const*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int mpegts_write_pmt(AVFormatContext *s, MpegTSService *service)
{
    MpegTSWrite *ts = s->priv_data;
    uint8_t data[SECTION_LENGTH], *q, *desc_length_ptr, *program_info_length_ptr;
    int val, stream_type, i, err = 0;

    q = data;
    put16(&q, 0xe000 | service->pcr_pid);

    program_info_length_ptr = q;
    q += 2; /* patched after */

    /* put program info here */

    val = 0xf000 | (q - program_info_length_ptr - 2);
    program_info_length_ptr[0] = val >> 8;
    program_info_length_ptr[1] = val;

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        MpegTSWriteStream *ts_st = st->priv_data;
        AVDictionaryEntry *lang = av_dict_get(st->metadata, "language", NULL, 0);

        if (s->nb_programs) {
            int k, found = 0;
            AVProgram *program = service->program;

            for (k = 0; k < program->nb_stream_indexes; k++)
                if (program->stream_index[k] == i) {
                    found = 1;
                    break;
                }

            if (!found)
                continue;
        }

        if (q - data > SECTION_LENGTH - 32) {
            err = 1;
            break;
        }
        switch (st->codecpar->codec_id) {
        case AV_CODEC_ID_MPEG1VIDEO:
        case AV_CODEC_ID_MPEG2VIDEO:
            stream_type = STREAM_TYPE_VIDEO_MPEG2;
            break;
        case AV_CODEC_ID_MPEG4:
            stream_type = STREAM_TYPE_VIDEO_MPEG4;
            break;
        case AV_CODEC_ID_H264:
            stream_type = STREAM_TYPE_VIDEO_H264;
            break;
        case AV_CODEC_ID_HEVC:
            stream_type = STREAM_TYPE_VIDEO_HEVC;
            break;
        case AV_CODEC_ID_CAVS:
            stream_type = STREAM_TYPE_VIDEO_CAVS;
            break;
        case AV_CODEC_ID_DIRAC:
            stream_type = STREAM_TYPE_VIDEO_DIRAC;
            break;
        case AV_CODEC_ID_VC1:
            stream_type = STREAM_TYPE_VIDEO_VC1;
            break;
        case AV_CODEC_ID_MP2:
        case AV_CODEC_ID_MP3:
            if (   st->codecpar->sample_rate > 0
                && st->codecpar->sample_rate < 32000) {
                stream_type = STREAM_TYPE_AUDIO_MPEG2;
            } else {
                stream_type = STREAM_TYPE_AUDIO_MPEG1;
            }
            break;
        case AV_CODEC_ID_AAC:
            stream_type = (ts->flags & MPEGTS_FLAG_AAC_LATM)
                          ? STREAM_TYPE_AUDIO_AAC_LATM
                          : STREAM_TYPE_AUDIO_AAC;
            break;
        case AV_CODEC_ID_AAC_LATM:
            stream_type = STREAM_TYPE_AUDIO_AAC_LATM;
            break;
        case AV_CODEC_ID_AC3:
            stream_type = (ts->flags & MPEGTS_FLAG_SYSTEM_B)
                          ? STREAM_TYPE_PRIVATE_DATA
                          : STREAM_TYPE_AUDIO_AC3;
            break;
        case AV_CODEC_ID_EAC3:
            stream_type = (ts->flags & MPEGTS_FLAG_SYSTEM_B)
                          ? STREAM_TYPE_PRIVATE_DATA
                          : STREAM_TYPE_AUDIO_EAC3;
            break;
        case AV_CODEC_ID_DTS:
            stream_type = STREAM_TYPE_AUDIO_DTS;
            break;
        case AV_CODEC_ID_TRUEHD:
            stream_type = STREAM_TYPE_AUDIO_TRUEHD;
            break;
        case AV_CODEC_ID_OPUS:
            stream_type = STREAM_TYPE_PRIVATE_DATA;
            break;
        case AV_CODEC_ID_TIMED_ID3:
            stream_type = STREAM_TYPE_METADATA;
            break;
        default:
            stream_type = STREAM_TYPE_PRIVATE_DATA;
            break;
        }

        *q++ = stream_type;
        put16(&q, 0xe000 | ts_st->pid);
        desc_length_ptr = q;
        q += 2; /* patched after */

        /* write optional descriptors here */
        switch (st->codecpar->codec_type) {
        case AVMEDIA_TYPE_AUDIO:
            if (st->codecpar->codec_id==AV_CODEC_ID_AC3 && (ts->flags & MPEGTS_FLAG_SYSTEM_B)) {
                *q++=0x6a; // AC3 descriptor see A038 DVB SI
                *q++=1; // 1 byte, all flags sets to 0
                *q++=0; // omit all fields...
            }
            if (st->codecpar->codec_id==AV_CODEC_ID_EAC3 && (ts->flags & MPEGTS_FLAG_SYSTEM_B)) {
                *q++=0x7a; // EAC3 descriptor see A038 DVB SI
                *q++=1; // 1 byte, all flags sets to 0
                *q++=0; // omit all fields...
            }
            if (st->codecpar->codec_id==AV_CODEC_ID_S302M)
                put_registration_descriptor(&q, MKTAG('B', 'S', 'S', 'D'));
            if (st->codecpar->codec_id==AV_CODEC_ID_OPUS) {
                /* 6 bytes registration descriptor, 4 bytes Opus audio descriptor */
                if (q - data > SECTION_LENGTH - 6 - 4) {
                    err = 1;
                    break;
                }

                put_registration_descriptor(&q, MKTAG('O', 'p', 'u', 's'));

                *q++ = 0x7f; /* DVB extension descriptor */
                *q++ = 2;
                *q++ = 0x80;

                if (st->codecpar->extradata && st->codecpar->extradata_size >= 19) {
                    if (st->codecpar->extradata[18] == 0 && st->codecpar->channels <= 2) {
                        /* RTP mapping family */
                        *q++ = st->codecpar->channels;
                    } else if (st->codecpar->extradata[18] == 1 && st->codecpar->channels <= 8 &&
                               st->codecpar->extradata_size >= 21 + st->codecpar->channels) {
                        static const uint8_t coupled_stream_counts[9] = {
                            1, 0, 1, 1, 2, 2, 2, 3, 3
                        };
                        static const uint8_t channel_map_a[8][8] = {
                            {0},
                            {0, 1},
                            {0, 2, 1},
                            {0, 1, 2, 3},
                            {0, 4, 1, 2, 3},
                            {0, 4, 1, 2, 3, 5},
                            {0, 4, 1, 2, 3, 5, 6},
                            {0, 6, 1, 2, 3, 4, 5, 7},
                        };
                        static const uint8_t channel_map_b[8][8] = {
                            {0},
                            {0, 1},
                            {0, 1, 2},
                            {0, 1, 2, 3},
                            {0, 1, 2, 3, 4},
                            {0, 1, 2, 3, 4, 5},
                            {0, 1, 2, 3, 4, 5, 6},
                            {0, 1, 2, 3, 4, 5, 6, 7},
                        };
                        /* Vorbis mapping family */

                        if (st->codecpar->extradata[19] == st->codecpar->channels - coupled_stream_counts[st->codecpar->channels] &&
                            st->codecpar->extradata[20] == coupled_stream_counts[st->codecpar->channels] &&
                            memcmp(&st->codecpar->extradata[21], channel_map_a[st->codecpar->channels-1], st->codecpar->channels) == 0) {
                            *q++ = st->codecpar->channels;
                        } else if (st->codecpar->channels >= 2 && st->codecpar->extradata[19] == st->codecpar->channels &&
                                   st->codecpar->extradata[20] == 0 &&
                                   memcmp(&st->codecpar->extradata[21], channel_map_b[st->codecpar->channels-1], st->codecpar->channels) == 0) {
                            *q++ = st->codecpar->channels | 0x80;
                        } else {
                            /* Unsupported, could write an extended descriptor here */
                            av_log(s, AV_LOG_ERROR, "Unsupported Opus Vorbis-style channel mapping");
                            *q++ = 0xff;
                        }
                    } else {
                        /* Unsupported */
                        av_log(s, AV_LOG_ERROR, "Unsupported Opus channel mapping for family %d", st->codecpar->extradata[18]);
                        *q++ = 0xff;
                    }
                } else if (st->codecpar->channels <= 2) {
                    /* Assume RTP mapping family */
                    *q++ = st->codecpar->channels;
                } else {
                    /* Unsupported */
                    av_log(s, AV_LOG_ERROR, "Unsupported Opus channel mapping");
                    *q++ = 0xff;
                }
            }

            if (lang) {
                char *p;
                char *next = lang->value;
                uint8_t *len_ptr;

                *q++     = 0x0a; /* ISO 639 language descriptor */
                len_ptr  = q++;
                *len_ptr = 0;

                for (p = lang->value; next && *len_ptr < 255 / 4 * 4; p = next + 1) {
                    if (q - data > SECTION_LENGTH - 4) {
                        err = 1;
                        break;
                    }
                    next = strchr(p, ',');
                    if (strlen(p) != 3 && (!next || next != p + 3))
                        continue; /* not a 3-letter code */

                    *q++ = *p++;
                    *q++ = *p++;
                    *q++ = *p++;

                    if (st->disposition & AV_DISPOSITION_CLEAN_EFFECTS)
                        *q++ = 0x01;
                    else if (st->disposition & AV_DISPOSITION_HEARING_IMPAIRED)
                        *q++ = 0x02;
                    else if (st->disposition & AV_DISPOSITION_VISUAL_IMPAIRED)
                        *q++ = 0x03;
                    else
                        *q++ = 0; /* undefined type */

                    *len_ptr += 4;
                }

                if (*len_ptr == 0)
                    q -= 2; /* no language codes were written */
            }
            break;
        case AVMEDIA_TYPE_SUBTITLE:
        {
           const char default_language[] = "und";
           const char *language = lang && strlen(lang->value) >= 3 ? lang->value : default_language;

           if (st->codecpar->codec_id == AV_CODEC_ID_DVB_SUBTITLE) {
               uint8_t *len_ptr;
               int extradata_copied = 0;

               *q++ = 0x59; /* subtitling_descriptor */
               len_ptr = q++;

               while (strlen(language) >= 3) {
                   if (sizeof(data) - (q - data) < 8) { /* 8 bytes per DVB subtitle substream data */
                       err = 1;
                       break;
                   }
                   *q++ = *language++;
                   *q++ = *language++;
                   *q++ = *language++;
                   /* Skip comma */
                   if (*language != '\0')
                       language++;

                   if (st->codecpar->extradata_size - extradata_copied >= 5) {
                       *q++ = st->codecpar->extradata[extradata_copied + 4]; /* subtitling_type */
                       memcpy(q, st->codecpar->extradata + extradata_copied, 4); /* composition_page_id and ancillary_page_id */
                       extradata_copied += 5;
                       q += 4;
                   } else {
                       /* subtitling_type:
                        * 0x10 - normal with no monitor aspect ratio criticality
                        * 0x20 - for the hard of hearing with no monitor aspect ratio criticality */
                       *q++ = (st->disposition & AV_DISPOSITION_HEARING_IMPAIRED) ? 0x20 : 0x10;
                       if ((st->codecpar->extradata_size == 4) && (extradata_copied == 0)) {
                           /* support of old 4-byte extradata format */
                           memcpy(q, st->codecpar->extradata, 4); /* composition_page_id and ancillary_page_id */
                           extradata_copied += 4;
                           q += 4;
                       } else {
                           put16(&q, 1); /* composition_page_id */
                           put16(&q, 1); /* ancillary_page_id */
                       }
                   }
               }

               *len_ptr = q - len_ptr - 1;
           } else if (st->codecpar->codec_id == AV_CODEC_ID_DVB_TELETEXT) {
               uint8_t *len_ptr = NULL;
               int extradata_copied = 0;

               /* The descriptor tag. teletext_descriptor */
               *q++ = 0x56;
               len_ptr = q++;

               while (strlen(language) >= 3 && q - data < sizeof(data) - 6) {
                   *q++ = *language++;
                   *q++ = *language++;
                   *q++ = *language++;
                   /* Skip comma */
                   if (*language != '\0')
                       language++;

                   if (st->codecpar->extradata_size - 1 > extradata_copied) {
                       memcpy(q, st->codecpar->extradata + extradata_copied, 2);
                       extradata_copied += 2;
                       q += 2;
                   } else {
                       /* The Teletext descriptor:
                        * teletext_type: This 5-bit field indicates the type of Teletext page indicated. (0x01 Initial Teletext page)
                        * teletext_magazine_number: This is a 3-bit field which identifies the magazine number.
                        * teletext_page_number: This is an 8-bit field giving two 4-bit hex digits identifying the page number. */
                       *q++ = 0x08;
                       *q++ = 0x00;
                   }
               }

               *len_ptr = q - len_ptr - 1;
            }
        }
        break;
        case AVMEDIA_TYPE_VIDEO:
            if (stream_type == STREAM_TYPE_VIDEO_DIRAC) {
                put_registration_descriptor(&q, MKTAG('d', 'r', 'a', 'c'));
            } else if (stream_type == STREAM_TYPE_VIDEO_VC1) {
                put_registration_descriptor(&q, MKTAG('V', 'C', '-', '1'));
            } else if (stream_type == STREAM_TYPE_VIDEO_HEVC && s->strict_std_compliance <= FF_COMPLIANCE_NORMAL) {
                put_registration_descriptor(&q, MKTAG('H', 'E', 'V', 'C'));
            }
            break;
        case AVMEDIA_TYPE_DATA:
            if (st->codecpar->codec_id == AV_CODEC_ID_SMPTE_KLV) {
                put_registration_descriptor(&q, MKTAG('K', 'L', 'V', 'A'));
            } else if (st->codecpar->codec_id == AV_CODEC_ID_TIMED_ID3) {
                const char *tag = "ID3 ";
                *q++ = 0x26; /* metadata descriptor */
                *q++ = 13;
                put16(&q, 0xffff);    /* metadata application format */
                putbuf(&q, tag, strlen(tag));
                *q++ = 0xff;        /* metadata format */
                putbuf(&q, tag, strlen(tag));
                *q++ = 0;            /* metadata service ID */
                *q++ = 0xF;          /* metadata_locator_record_flag|MPEG_carriage_flags|reserved */
            }
            break;
        }

        val = 0xf000 | (q - desc_length_ptr - 2);
        desc_length_ptr[0] = val >> 8;
        desc_length_ptr[1] = val;
    }

    if (err)
        av_log(s, AV_LOG_ERROR,
               "The PMT section cannot fit stream %d and all following streams.\n"
               "Try reducing the number of languages in the audio streams "
               "or the total number of streams.\n", i);

    mpegts_write_section1(&service->pmt, PMT_TID, service->sid, ts->tables_version, 0, 0,
                          data, q - data);
    return 0;
}