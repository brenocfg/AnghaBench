#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* int64_t ;
struct TYPE_15__ {char* key; char* value; } ;
struct TYPE_14__ {double duration; int /*<<< orphan*/  metadata; TYPE_3__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_13__ {int flags; void* metadata_size_pos; double framerate; double datasize; double videosize; double audiosize; unsigned int metadata_totalsize; void* metadata_totalsize_pos; void* keyframes_info_offset; scalar_t__ lastkeyframelocation; void* lastkeyframelocation_offset; scalar_t__ lastkeyframetimestamp; void* lastkeyframetimestamp_offset; scalar_t__ lasttimestamp; void* lasttimestamp_offset; void* audiosize_offset; void* videosize_offset; void* datasize_offset; TYPE_2__* audio_par; TYPE_1__* video_par; scalar_t__ keyframe_index_size; scalar_t__ acurframeindex; void* filesize_offset; scalar_t__ data_par; void* duration_offset; } ;
struct TYPE_12__ {double bit_rate; double sample_rate; scalar_t__ codec_id; int channels; double codec_tag; } ;
struct TYPE_11__ {double width; double height; double bit_rate; double codec_tag; } ;
typedef  TYPE_3__ FLVContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AMF_DATA_TYPE_MIXEDARRAY ; 
 int /*<<< orphan*/  AMF_DATA_TYPE_OBJECT ; 
 int /*<<< orphan*/  AMF_DATA_TYPE_STRING ; 
 int /*<<< orphan*/  AMF_END_OF_OBJECT ; 
 scalar_t__ AV_CODEC_ID_PCM_U8 ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 double AV_TIME_BASE ; 
 int FLV_ADD_KEYFRAME_INDEX ; 
 int FLV_NO_DURATION_FILESIZE ; 
 int /*<<< orphan*/  FLV_TAG_TYPE_META ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_5__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 void* avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_standardize_creation_time (TYPE_4__*) ; 
 int /*<<< orphan*/  put_amf_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_amf_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_amf_double (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  put_amf_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void write_metadata(AVFormatContext *s, unsigned int ts)
{
    AVIOContext *pb = s->pb;
    FLVContext *flv = s->priv_data;
    int write_duration_filesize = !(flv->flags & FLV_NO_DURATION_FILESIZE);
    int metadata_count = 0;
    int64_t metadata_count_pos;
    AVDictionaryEntry *tag = NULL;

    /* write meta_tag */
    avio_w8(pb, FLV_TAG_TYPE_META);            // tag type META
    flv->metadata_size_pos = avio_tell(pb);
    avio_wb24(pb, 0);           // size of data part (sum of all parts below)
    avio_wb24(pb, ts);          // timestamp
    avio_wb32(pb, 0);           // reserved

    /* now data of data_size size */

    /* first event name as a string */
    avio_w8(pb, AMF_DATA_TYPE_STRING);
    put_amf_string(pb, "onMetaData"); // 12 bytes

    /* mixed array (hash) with size and string/type/data tuples */
    avio_w8(pb, AMF_DATA_TYPE_MIXEDARRAY);
    metadata_count_pos = avio_tell(pb);
    metadata_count = 4 * !!flv->video_par +
                     5 * !!flv->audio_par +
                     1 * !!flv->data_par;
    if (write_duration_filesize) {
        metadata_count += 2; // +2 for duration and file size
    }
    avio_wb32(pb, metadata_count);

    if (write_duration_filesize) {
        put_amf_string(pb, "duration");
        flv->duration_offset = avio_tell(pb);
        // fill in the guessed duration, it'll be corrected later if incorrect
        put_amf_double(pb, s->duration / AV_TIME_BASE);
    }

    if (flv->video_par) {
        put_amf_string(pb, "width");
        put_amf_double(pb, flv->video_par->width);

        put_amf_string(pb, "height");
        put_amf_double(pb, flv->video_par->height);

        put_amf_string(pb, "videodatarate");
        put_amf_double(pb, flv->video_par->bit_rate / 1024.0);

        if (flv->framerate != 0.0) {
            put_amf_string(pb, "framerate");
            put_amf_double(pb, flv->framerate);
            metadata_count++;
        }

        put_amf_string(pb, "videocodecid");
        put_amf_double(pb, flv->video_par->codec_tag);
    }

    if (flv->audio_par) {
        put_amf_string(pb, "audiodatarate");
        put_amf_double(pb, flv->audio_par->bit_rate / 1024.0);

        put_amf_string(pb, "audiosamplerate");
        put_amf_double(pb, flv->audio_par->sample_rate);

        put_amf_string(pb, "audiosamplesize");
        put_amf_double(pb, flv->audio_par->codec_id == AV_CODEC_ID_PCM_U8 ? 8 : 16);

        put_amf_string(pb, "stereo");
        put_amf_bool(pb, flv->audio_par->channels == 2);

        put_amf_string(pb, "audiocodecid");
        put_amf_double(pb, flv->audio_par->codec_tag);
    }

    if (flv->data_par) {
        put_amf_string(pb, "datastream");
        put_amf_double(pb, 0.0);
    }

    ff_standardize_creation_time(s);
    while ((tag = av_dict_get(s->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
        if(   !strcmp(tag->key, "width")
            ||!strcmp(tag->key, "height")
            ||!strcmp(tag->key, "videodatarate")
            ||!strcmp(tag->key, "framerate")
            ||!strcmp(tag->key, "videocodecid")
            ||!strcmp(tag->key, "audiodatarate")
            ||!strcmp(tag->key, "audiosamplerate")
            ||!strcmp(tag->key, "audiosamplesize")
            ||!strcmp(tag->key, "stereo")
            ||!strcmp(tag->key, "audiocodecid")
            ||!strcmp(tag->key, "duration")
            ||!strcmp(tag->key, "onMetaData")
            ||!strcmp(tag->key, "datasize")
            ||!strcmp(tag->key, "lasttimestamp")
            ||!strcmp(tag->key, "totalframes")
            ||!strcmp(tag->key, "hasAudio")
            ||!strcmp(tag->key, "hasVideo")
            ||!strcmp(tag->key, "hasCuePoints")
            ||!strcmp(tag->key, "hasMetadata")
            ||!strcmp(tag->key, "hasKeyframes")
        ){
            av_log(s, AV_LOG_DEBUG, "Ignoring metadata for %s\n", tag->key);
            continue;
        }
        put_amf_string(pb, tag->key);
        avio_w8(pb, AMF_DATA_TYPE_STRING);
        put_amf_string(pb, tag->value);
        metadata_count++;
    }

    if (write_duration_filesize) {
        put_amf_string(pb, "filesize");
        flv->filesize_offset = avio_tell(pb);
        put_amf_double(pb, 0); // delayed write
    }

    if (flv->flags & FLV_ADD_KEYFRAME_INDEX) {
        flv->acurframeindex = 0;
        flv->keyframe_index_size = 0;

        put_amf_string(pb, "hasVideo");
        put_amf_bool(pb, !!flv->video_par);
        metadata_count++;

        put_amf_string(pb, "hasKeyframes");
        put_amf_bool(pb, 1);
        metadata_count++;

        put_amf_string(pb, "hasAudio");
        put_amf_bool(pb, !!flv->audio_par);
        metadata_count++;

        put_amf_string(pb, "hasMetadata");
        put_amf_bool(pb, 1);
        metadata_count++;

        put_amf_string(pb, "canSeekToEnd");
        put_amf_bool(pb, 1);
        metadata_count++;

        put_amf_string(pb, "datasize");
        flv->datasize_offset = avio_tell(pb);
        flv->datasize = 0;
        put_amf_double(pb, flv->datasize);
        metadata_count++;

        put_amf_string(pb, "videosize");
        flv->videosize_offset = avio_tell(pb);
        flv->videosize = 0;
        put_amf_double(pb, flv->videosize);
        metadata_count++;

        put_amf_string(pb, "audiosize");
        flv->audiosize_offset = avio_tell(pb);
        flv->audiosize = 0;
        put_amf_double(pb, flv->audiosize);
        metadata_count++;

        put_amf_string(pb, "lasttimestamp");
        flv->lasttimestamp_offset = avio_tell(pb);
        flv->lasttimestamp = 0;
        put_amf_double(pb, 0);
        metadata_count++;

        put_amf_string(pb, "lastkeyframetimestamp");
        flv->lastkeyframetimestamp_offset = avio_tell(pb);
        flv->lastkeyframetimestamp = 0;
        put_amf_double(pb, 0);
        metadata_count++;

        put_amf_string(pb, "lastkeyframelocation");
        flv->lastkeyframelocation_offset = avio_tell(pb);
        flv->lastkeyframelocation = 0;
        put_amf_double(pb, 0);
        metadata_count++;

        put_amf_string(pb, "keyframes");
        put_amf_byte(pb, AMF_DATA_TYPE_OBJECT);
        metadata_count++;

        flv->keyframes_info_offset = avio_tell(pb);
    }

    put_amf_string(pb, "");
    avio_w8(pb, AMF_END_OF_OBJECT);

    /* write total size of tag */
    flv->metadata_totalsize = avio_tell(pb) - flv->metadata_size_pos - 10;

    avio_seek(pb, metadata_count_pos, SEEK_SET);
    avio_wb32(pb, metadata_count);

    avio_seek(pb, flv->metadata_size_pos, SEEK_SET);
    avio_wb24(pb, flv->metadata_totalsize);
    avio_skip(pb, flv->metadata_totalsize + 10 - 3);
    flv->metadata_totalsize_pos = avio_tell(pb);
    avio_wb32(pb, flv->metadata_totalsize + 11);
}