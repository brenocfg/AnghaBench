#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  str_val ;
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {int flags; TYPE_2__* priv_data; } ;
struct TYPE_7__ {unsigned int keyframe_count; scalar_t__* keyframe_times; scalar_t__* keyframe_filepositions; unsigned int validate_count; TYPE_1__* validate_index; } ;
struct TYPE_6__ {scalar_t__ dts; scalar_t__ pos; } ;
typedef  TYPE_2__ FLVContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AMF_DATA_TYPE_ARRAY ; 
 scalar_t__ AMF_DATA_TYPE_NUMBER ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFMT_FLAG_IGNIDX ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 unsigned int FFMIN (int,unsigned int) ; 
 int /*<<< orphan*/  KEYFRAMES_BYTEOFFSET_TAG ; 
 int /*<<< orphan*/  KEYFRAMES_TIMESTAMP_TAG ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ amf_get_string (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_freep (scalar_t__**) ; 
 scalar_t__ av_int2double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__* av_mallocz (int) ; 
 scalar_t__ avio_r8 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int parse_keyframes_index(AVFormatContext *s, AVIOContext *ioc, int64_t max_pos)
{
    FLVContext *flv       = s->priv_data;
    unsigned int timeslen = 0, fileposlen = 0, i;
    char str_val[256];
    int64_t *times         = NULL;
    int64_t *filepositions = NULL;
    int ret                = AVERROR(ENOSYS);
    int64_t initial_pos    = avio_tell(ioc);

    if (flv->keyframe_count > 0) {
        av_log(s, AV_LOG_DEBUG, "keyframes have been parsed\n");
        return 0;
    }
    av_assert0(!flv->keyframe_times);
    av_assert0(!flv->keyframe_filepositions);

    if (s->flags & AVFMT_FLAG_IGNIDX)
        return 0;

    while (avio_tell(ioc) < max_pos - 2 &&
           amf_get_string(ioc, str_val, sizeof(str_val)) > 0) {
        int64_t **current_array;
        unsigned int arraylen;

        // Expect array object in context
        if (avio_r8(ioc) != AMF_DATA_TYPE_ARRAY)
            break;

        arraylen = avio_rb32(ioc);
        if (arraylen>>28)
            break;

        if       (!strcmp(KEYFRAMES_TIMESTAMP_TAG , str_val) && !times) {
            current_array = &times;
            timeslen      = arraylen;
        } else if (!strcmp(KEYFRAMES_BYTEOFFSET_TAG, str_val) &&
                   !filepositions) {
            current_array = &filepositions;
            fileposlen    = arraylen;
        } else
            // unexpected metatag inside keyframes, will not use such
            // metadata for indexing
            break;

        if (!(*current_array = av_mallocz(sizeof(**current_array) * arraylen))) {
            ret = AVERROR(ENOMEM);
            goto finish;
        }

        for (i = 0; i < arraylen && avio_tell(ioc) < max_pos - 1; i++) {
            if (avio_r8(ioc) != AMF_DATA_TYPE_NUMBER)
                goto invalid;
            current_array[0][i] = av_int2double(avio_rb64(ioc));
        }
        if (times && filepositions) {
            // All done, exiting at a position allowing amf_parse_object
            // to finish parsing the object
            ret = 0;
            break;
        }
    }

    if (timeslen == fileposlen && fileposlen>1 && max_pos <= filepositions[0]) {
        for (i = 0; i < FFMIN(2,fileposlen); i++) {
            flv->validate_index[i].pos = filepositions[i];
            flv->validate_index[i].dts = times[i] * 1000;
            flv->validate_count        = i + 1;
        }
        flv->keyframe_times = times;
        flv->keyframe_filepositions = filepositions;
        flv->keyframe_count = timeslen;
        times = NULL;
        filepositions = NULL;
    } else {
invalid:
        av_log(s, AV_LOG_WARNING, "Invalid keyframes object, skipping.\n");
    }

finish:
    av_freep(&times);
    av_freep(&filepositions);
    avio_seek(ioc, initial_pos, SEEK_SET);
    return ret;
}