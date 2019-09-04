#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_20__ ;
typedef  struct TYPE_37__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
struct TYPE_45__ {int duration; int nb_languages; char const** languages; int nb_packets; int data_offset; scalar_t__ is_streamed; TYPE_1__* streams; int /*<<< orphan*/  creation_time; } ;
struct TYPE_44__ {char* name; } ;
struct TYPE_39__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_43__ {int bit_rate; int codec_type; int extradata_size; scalar_t__ codec_id; int block_align; int width; int height; int codec_tag; TYPE_2__ sample_aspect_ratio; } ;
struct TYPE_42__ {char const* value; char const* key; } ;
struct TYPE_41__ {int nb_streams; int packet_size; TYPE_20__** streams; scalar_t__ nb_chapters; int /*<<< orphan*/  metadata; TYPE_3__* pb; TYPE_8__* priv_data; } ;
struct TYPE_40__ {int seekable; } ;
struct TYPE_38__ {TYPE_6__* codecpar; int /*<<< orphan*/  metadata; } ;
struct TYPE_37__ {int stream_language_index; int num; int seq; } ;
typedef  TYPE_2__ AVRational ;
typedef  TYPE_3__ AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVDictionaryEntry ;
typedef  TYPE_6__ AVCodecParameters ;
typedef  TYPE_7__ AVCodecDescriptor ;
typedef  TYPE_8__ ASFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_SEEKABLE_NORMAL ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 scalar_t__ AV_CODEC_ID_ADPCM_G726 ; 
 scalar_t__ AV_CODEC_ID_WMAV2 ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LANG_ISO639_1 ; 
 scalar_t__ DATA_HEADER_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (TYPE_5__**) ; 
 int /*<<< orphan*/  FF_PUT_WAV_HEADER_FORCE_WAVEFORMATEX ; 
 int PREROLL_TIME ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int asf_write_markers (TYPE_4__*) ; 
 int av_dict_count (int /*<<< orphan*/ ) ; 
 TYPE_5__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 TYPE_7__* avcodec_descriptor_get (scalar_t__) ; 
 int avio_close_dyn_buf (TYPE_3__*,int /*<<< orphan*/ **) ; 
 scalar_t__ avio_open_dyn_buf (TYPE_3__**) ; 
 int avio_put_str16le (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int avio_tell (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_w8 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  avio_wl16 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  avio_wl32 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  avio_wl64 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  avio_write (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_20__*,int,int,int) ; 
 int /*<<< orphan*/  end_header (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ff_asf_audio_conceal_spread ; 
 int /*<<< orphan*/  ff_asf_audio_stream ; 
 int /*<<< orphan*/  ff_asf_codec_comment1_header ; 
 int /*<<< orphan*/  ff_asf_codec_comment_header ; 
 int /*<<< orphan*/  ff_asf_comment_header ; 
 int /*<<< orphan*/  ff_asf_data_header ; 
 int /*<<< orphan*/  ff_asf_extended_content_header ; 
 int /*<<< orphan*/  ff_asf_extended_stream_properties_object ; 
 int /*<<< orphan*/  ff_asf_file_header ; 
 int /*<<< orphan*/  ff_asf_group_mutual_exclusion_object ; 
 int /*<<< orphan*/  ff_asf_head1_guid ; 
 int /*<<< orphan*/  ff_asf_head2_guid ; 
 int /*<<< orphan*/  ff_asf_header ; 
 int /*<<< orphan*/  ff_asf_language_guid ; 
 int /*<<< orphan*/  ff_asf_metadata_conv ; 
 int /*<<< orphan*/  ff_asf_metadata_header ; 
 int /*<<< orphan*/  ff_asf_mutex_language ; 
 int /*<<< orphan*/  ff_asf_my_guid ; 
 int /*<<< orphan*/  ff_asf_stream_header ; 
 int /*<<< orphan*/  ff_asf_video_conceal_none ; 
 int /*<<< orphan*/  ff_asf_video_stream ; 
 char* ff_convert_lang_to (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_metadata_conv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_parse_creation_time_metadata (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_put_bmp_header (TYPE_3__*,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_put_guid (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_put_wav_header (TYPE_4__*,TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_chunk (TYPE_4__*,int,int /*<<< orphan*/ ,int) ; 
 int put_header (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_str16 (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int unix_to_file_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asf_write_header1(AVFormatContext *s, int64_t file_size,
                             int64_t data_chunk_size)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    AVDictionaryEntry *tags[5];
    int header_size, n, extra_size, extra_size2, wav_extra_size;
    int has_title, has_aspect_ratio = 0;
    int metadata_count;
    AVCodecParameters *par;
    int64_t header_offset, cur_pos, hpos;
    int bit_rate;
    int64_t duration;
    int audio_language_counts[128] = { 0 };

    ff_metadata_conv(&s->metadata, ff_asf_metadata_conv, NULL);

    tags[0] = av_dict_get(s->metadata, "title", NULL, 0);
    tags[1] = av_dict_get(s->metadata, "author", NULL, 0);
    tags[2] = av_dict_get(s->metadata, "copyright", NULL, 0);
    tags[3] = av_dict_get(s->metadata, "comment", NULL, 0);
    tags[4] = av_dict_get(s->metadata, "rating", NULL, 0);

    duration       = asf->duration + PREROLL_TIME * 10000;
    has_title      = tags[0] || tags[1] || tags[2] || tags[3] || tags[4];

    if (!file_size) {
        if (ff_parse_creation_time_metadata(s, &asf->creation_time, 0) != 0)
            av_dict_set(&s->metadata, "creation_time", NULL, 0);
    }

    metadata_count = av_dict_count(s->metadata);

    bit_rate = 0;
    for (n = 0; n < s->nb_streams; n++) {
        AVDictionaryEntry *entry;
        par = s->streams[n]->codecpar;

        avpriv_set_pts_info(s->streams[n], 32, 1, 1000); /* 32 bit pts in ms */

        bit_rate += par->bit_rate;
        if (   par->codec_type == AVMEDIA_TYPE_VIDEO
            && par->sample_aspect_ratio.num > 0
            && par->sample_aspect_ratio.den > 0)
            has_aspect_ratio++;

        entry = av_dict_get(s->streams[n]->metadata, "language", NULL, 0);
        if (entry) {
            const char *iso6391lang = ff_convert_lang_to(entry->value, AV_LANG_ISO639_1);
            if (iso6391lang) {
                int i;
                for (i = 0; i < asf->nb_languages; i++) {
                    if (!strcmp(asf->languages[i], iso6391lang)) {
                        asf->streams[n].stream_language_index = i;
                        break;
                    }
                }
                if (i >= asf->nb_languages) {
                    asf->languages[asf->nb_languages] = iso6391lang;
                    asf->streams[n].stream_language_index = asf->nb_languages;
                    asf->nb_languages++;
                }
                if (par->codec_type == AVMEDIA_TYPE_AUDIO)
                    audio_language_counts[asf->streams[n].stream_language_index]++;
            }
        } else {
            asf->streams[n].stream_language_index = 128;
        }
    }

    if (asf->is_streamed) {
        put_chunk(s, 0x4824, 0, 0xc00); /* start of stream (length will be patched later) */
    }

    ff_put_guid(pb, &ff_asf_header);
    avio_wl64(pb, -1); /* header length, will be patched after */
    avio_wl32(pb, 3 + has_title + !!metadata_count + s->nb_streams); /* number of chunks in header */
    avio_w8(pb, 1); /* ??? */
    avio_w8(pb, 2); /* ??? */

    /* file header */
    header_offset = avio_tell(pb);
    hpos          = put_header(pb, &ff_asf_file_header);
    ff_put_guid(pb, &ff_asf_my_guid);
    avio_wl64(pb, file_size);
    avio_wl64(pb, unix_to_file_time(asf->creation_time));
    avio_wl64(pb, asf->nb_packets); /* number of packets */
    avio_wl64(pb, duration); /* end time stamp (in 100ns units) */
    avio_wl64(pb, asf->duration); /* duration (in 100ns units) */
    avio_wl64(pb, PREROLL_TIME); /* start time stamp */
    avio_wl32(pb, (asf->is_streamed || !(pb->seekable & AVIO_SEEKABLE_NORMAL)) ? 3 : 2);  /* ??? */
    avio_wl32(pb, s->packet_size); /* packet size */
    avio_wl32(pb, s->packet_size); /* packet size */
    avio_wl32(pb, bit_rate ? bit_rate : -1); /* Maximum data rate in bps */
    end_header(pb, hpos);

    /* header_extension */
    hpos = put_header(pb, &ff_asf_head1_guid);
    ff_put_guid(pb, &ff_asf_head2_guid);
    avio_wl16(pb, 6);
    avio_wl32(pb, 0); /* length, to be filled later */
    if (asf->nb_languages) {
        int64_t hpos2;
        int i;
        int nb_audio_languages = 0;

        hpos2 = put_header(pb, &ff_asf_language_guid);
        avio_wl16(pb, asf->nb_languages);
        for (i = 0; i < asf->nb_languages; i++) {
            avio_w8(pb, 6);
            avio_put_str16le(pb, asf->languages[i]);
        }
        end_header(pb, hpos2);

        for (i = 0; i < asf->nb_languages; i++)
            if (audio_language_counts[i])
                nb_audio_languages++;

        if (nb_audio_languages > 1) {
            hpos2 = put_header(pb, &ff_asf_group_mutual_exclusion_object);
            ff_put_guid(pb, &ff_asf_mutex_language);
            avio_wl16(pb, nb_audio_languages);
            for (i = 0; i < asf->nb_languages; i++) {
                if (audio_language_counts[i]) {
                    avio_wl16(pb, audio_language_counts[i]);
                    for (n = 0; n < s->nb_streams; n++)
                        if (asf->streams[n].stream_language_index == i && s->streams[n]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
                            avio_wl16(pb, n + 1);
                }
            }
            end_header(pb, hpos2);
        }

        for (n = 0; n < s->nb_streams; n++) {
            int64_t es_pos;
            if (asf->streams[n].stream_language_index > 127)
                continue;
            es_pos = put_header(pb, &ff_asf_extended_stream_properties_object);
            avio_wl64(pb, 0); /* start time */
            avio_wl64(pb, 0); /* end time */
            avio_wl32(pb, s->streams[n]->codecpar->bit_rate); /* data bitrate bps */
            avio_wl32(pb, 5000); /* buffer size ms */
            avio_wl32(pb, 0); /* initial buffer fullness */
            avio_wl32(pb, s->streams[n]->codecpar->bit_rate); /* peak data bitrate */
            avio_wl32(pb, 5000); /* maximum buffer size ms */
            avio_wl32(pb, 0); /* max initial buffer fullness */
            avio_wl32(pb, 0); /* max object size */
            avio_wl32(pb, (!asf->is_streamed && (pb->seekable & AVIO_SEEKABLE_NORMAL)) << 1); /* flags - seekable */
            avio_wl16(pb, n + 1); /* stream number */
            avio_wl16(pb, asf->streams[n].stream_language_index); /* language id index */
            avio_wl64(pb, 0); /* avg time per frame */
            avio_wl16(pb, 0); /* stream name count */
            avio_wl16(pb, 0); /* payload extension system count */
            end_header(pb, es_pos);
        }
    }
    if (has_aspect_ratio) {
        int64_t hpos2;
        hpos2 = put_header(pb, &ff_asf_metadata_header);
        avio_wl16(pb, 2 * has_aspect_ratio);
        for (n = 0; n < s->nb_streams; n++) {
            par = s->streams[n]->codecpar;
            if (   par->codec_type == AVMEDIA_TYPE_VIDEO
                && par->sample_aspect_ratio.num > 0
                && par->sample_aspect_ratio.den > 0) {
                AVRational sar = par->sample_aspect_ratio;
                avio_wl16(pb, 0);
                // the stream number is set like this below
                avio_wl16(pb, n + 1);
                avio_wl16(pb, 26); // name_len
                avio_wl16(pb,  3); // value_type
                avio_wl32(pb,  4); // value_len
                avio_put_str16le(pb, "AspectRatioX");
                avio_wl32(pb, sar.num);
                avio_wl16(pb, 0);
                // the stream number is set like this below
                avio_wl16(pb, n + 1);
                avio_wl16(pb, 26); // name_len
                avio_wl16(pb,  3); // value_type
                avio_wl32(pb,  4); // value_len
                avio_put_str16le(pb, "AspectRatioY");
                avio_wl32(pb, sar.den);
            }
        }
        end_header(pb, hpos2);
    }
    {
        int64_t pos1;
        pos1 = avio_tell(pb);
        avio_seek(pb, hpos + 42, SEEK_SET);
        avio_wl32(pb, pos1 - hpos - 46);
        avio_seek(pb, pos1, SEEK_SET);
    }
    end_header(pb, hpos);

    /* title and other info */
    if (has_title) {
        int len;
        uint8_t *buf;
        AVIOContext *dyn_buf;

        if (avio_open_dyn_buf(&dyn_buf) < 0)
            return AVERROR(ENOMEM);

        hpos = put_header(pb, &ff_asf_comment_header);

        for (n = 0; n < FF_ARRAY_ELEMS(tags); n++) {
            len = tags[n] ? avio_put_str16le(dyn_buf, tags[n]->value) : 0;
            avio_wl16(pb, len);
        }
        len = avio_close_dyn_buf(dyn_buf, &buf);
        avio_write(pb, buf, len);
        av_freep(&buf);
        end_header(pb, hpos);
    }
    if (metadata_count) {
        AVDictionaryEntry *tag = NULL;
        hpos = put_header(pb, &ff_asf_extended_content_header);
        avio_wl16(pb, metadata_count);
        while ((tag = av_dict_get(s->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
            put_str16(pb, tag->key);
            avio_wl16(pb, 0);
            put_str16(pb, tag->value);
        }
        end_header(pb, hpos);
    }
    /* chapters using ASF markers */
    if (!asf->is_streamed && s->nb_chapters) {
        int ret;
        if ((ret = asf_write_markers(s)) < 0)
            return ret;
    }
    /* stream headers */
    for (n = 0; n < s->nb_streams; n++) {
        int64_t es_pos;
        //        ASFStream *stream = &asf->streams[n];

        par                 = s->streams[n]->codecpar;
        asf->streams[n].num = n + 1;
        asf->streams[n].seq = 1;

        switch (par->codec_type) {
        case AVMEDIA_TYPE_AUDIO:
            wav_extra_size = 0;
            extra_size     = 18 + wav_extra_size;
            extra_size2    = 8;
            break;
        default:
        case AVMEDIA_TYPE_VIDEO:
            wav_extra_size = par->extradata_size;
            extra_size     = 0x33 + wav_extra_size;
            extra_size2    = 0;
            break;
        }

        hpos = put_header(pb, &ff_asf_stream_header);
        if (par->codec_type == AVMEDIA_TYPE_AUDIO) {
            ff_put_guid(pb, &ff_asf_audio_stream);
            ff_put_guid(pb, &ff_asf_audio_conceal_spread);
        } else {
            ff_put_guid(pb, &ff_asf_video_stream);
            ff_put_guid(pb, &ff_asf_video_conceal_none);
        }
        avio_wl64(pb, 0); /* ??? */
        es_pos = avio_tell(pb);
        avio_wl32(pb, extra_size); /* wav header len */
        avio_wl32(pb, extra_size2); /* additional data len */
        avio_wl16(pb, n + 1); /* stream number */
        avio_wl32(pb, 0); /* ??? */

        if (par->codec_type == AVMEDIA_TYPE_AUDIO) {
            /* WAVEFORMATEX header */
            int wavsize = ff_put_wav_header(s, pb, par, FF_PUT_WAV_HEADER_FORCE_WAVEFORMATEX);

            if (wavsize < 0)
                return -1;
            if (wavsize != extra_size) {
                cur_pos = avio_tell(pb);
                avio_seek(pb, es_pos, SEEK_SET);
                avio_wl32(pb, wavsize); /* wav header len */
                avio_seek(pb, cur_pos, SEEK_SET);
            }
            /* ERROR Correction */
            avio_w8(pb, 0x01);
            if (par->codec_id == AV_CODEC_ID_ADPCM_G726 || !par->block_align) {
                avio_wl16(pb, 0x0190);
                avio_wl16(pb, 0x0190);
            } else {
                avio_wl16(pb, par->block_align);
                avio_wl16(pb, par->block_align);
            }
            avio_wl16(pb, 0x01);
            avio_w8(pb, 0x00);
        } else {
            avio_wl32(pb, par->width);
            avio_wl32(pb, par->height);
            avio_w8(pb, 2); /* ??? */
            avio_wl16(pb, 40 + par->extradata_size); /* size */

            /* BITMAPINFOHEADER header */
            ff_put_bmp_header(pb, par, 1, 0);
        }
        end_header(pb, hpos);
    }

    /* media comments */

    hpos = put_header(pb, &ff_asf_codec_comment_header);
    ff_put_guid(pb, &ff_asf_codec_comment1_header);
    avio_wl32(pb, s->nb_streams);
    for (n = 0; n < s->nb_streams; n++) {
        const AVCodecDescriptor *codec_desc;
        const char *desc;

        par  = s->streams[n]->codecpar;
        codec_desc = avcodec_descriptor_get(par->codec_id);

        if (par->codec_type == AVMEDIA_TYPE_AUDIO)
            avio_wl16(pb, 2);
        else if (par->codec_type == AVMEDIA_TYPE_VIDEO)
            avio_wl16(pb, 1);
        else
            avio_wl16(pb, -1);

        if (par->codec_id == AV_CODEC_ID_WMAV2)
            desc = "Windows Media Audio V8";
        else
            desc = codec_desc ? codec_desc->name : NULL;

        if (desc) {
            AVIOContext *dyn_buf;
            uint8_t *buf;
            int len;

            if (avio_open_dyn_buf(&dyn_buf) < 0)
                return AVERROR(ENOMEM);

            avio_put_str16le(dyn_buf, desc);
            len = avio_close_dyn_buf(dyn_buf, &buf);
            avio_wl16(pb, len / 2); // "number of characters" = length in bytes / 2

            avio_write(pb, buf, len);
            av_freep(&buf);
        } else
            avio_wl16(pb, 0);

        avio_wl16(pb, 0); /* no parameters */

        /* id */
        if (par->codec_type == AVMEDIA_TYPE_AUDIO) {
            avio_wl16(pb, 2);
            avio_wl16(pb, par->codec_tag);
        } else {
            avio_wl16(pb, 4);
            avio_wl32(pb, par->codec_tag);
        }
        if (!par->codec_tag)
            return -1;
    }
    end_header(pb, hpos);

    /* patch the header size fields */

    cur_pos     = avio_tell(pb);
    header_size = cur_pos - header_offset;
    if (asf->is_streamed) {
        header_size += 8 + 30 + DATA_HEADER_SIZE;

        avio_seek(pb, header_offset - 10 - 30, SEEK_SET);
        avio_wl16(pb, header_size);
        avio_seek(pb, header_offset - 2 - 30, SEEK_SET);
        avio_wl16(pb, header_size);

        header_size -= 8 + 30 + DATA_HEADER_SIZE;
    }
    header_size += 24 + 6;
    avio_seek(pb, header_offset - 14, SEEK_SET);
    avio_wl64(pb, header_size);
    avio_seek(pb, cur_pos, SEEK_SET);

    /* movie chunk, followed by packets of packet_size */
    asf->data_offset = cur_pos;
    ff_put_guid(pb, &ff_asf_data_header);
    avio_wl64(pb, data_chunk_size);
    ff_put_guid(pb, &ff_asf_my_guid);
    avio_wl64(pb, asf->nb_packets); /* nb packets */
    avio_w8(pb, 1); /* ??? */
    avio_w8(pb, 1); /* ??? */
    return 0;
}