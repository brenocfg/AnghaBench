#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  metadata; TYPE_1__* pb; } ;
struct TYPE_11__ {scalar_t__ eof_reached; } ;
typedef  TYPE_1__ AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_WL32 (char*,void*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 char* av_mallocz (int) ; 
 scalar_t__ avio_feof (TYPE_1__*) ; 
 int avio_read (TYPE_1__*,char*,int) ; 
 void* avio_rl32 (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (TYPE_1__*,int) ; 
 int avio_tell (TYPE_1__*) ; 

int ff_read_riff_info(AVFormatContext *s, int64_t size)
{
    int64_t start, end, cur;
    AVIOContext *pb = s->pb;

    start = avio_tell(pb);
    end   = start + size;

    while ((cur = avio_tell(pb)) >= 0 &&
           cur <= end - 8 /* = tag + size */) {
        uint32_t chunk_code;
        int64_t chunk_size;
        char key[5] = { 0 };
        char *value;

        chunk_code = avio_rl32(pb);
        chunk_size = avio_rl32(pb);
        if (avio_feof(pb)) {
            if (chunk_code || chunk_size) {
                av_log(s, AV_LOG_WARNING, "INFO subchunk truncated\n");
                return AVERROR_INVALIDDATA;
            }
            return AVERROR_EOF;
        }
        if (chunk_size > end ||
            end - chunk_size < cur ||
            chunk_size == UINT_MAX) {
            avio_seek(pb, -9, SEEK_CUR);
            chunk_code = avio_rl32(pb);
            chunk_size = avio_rl32(pb);
            if (chunk_size > end || end - chunk_size < cur || chunk_size == UINT_MAX) {
                av_log(s, AV_LOG_WARNING, "too big INFO subchunk\n");
                return AVERROR_INVALIDDATA;
            }
        }

        chunk_size += (chunk_size & 1);

        if (!chunk_code) {
            if (chunk_size)
                avio_skip(pb, chunk_size);
            else if (pb->eof_reached) {
                av_log(s, AV_LOG_WARNING, "truncated file\n");
                return AVERROR_EOF;
            }
            continue;
        }

        value = av_mallocz(chunk_size + 1);
        if (!value) {
            av_log(s, AV_LOG_ERROR,
                   "out of memory, unable to read INFO tag\n");
            return AVERROR(ENOMEM);
        }

        AV_WL32(key, chunk_code);
        // Work around VC++ 2015 Update 1 code-gen bug:
        // https://connect.microsoft.com/VisualStudio/feedback/details/2291638
        key[4] = 0;

        if (avio_read(pb, value, chunk_size) != chunk_size) {
            av_log(s, AV_LOG_WARNING,
                   "premature end of file while reading INFO tag\n");
        }

        av_dict_set(&s->metadata, key, value, AV_DICT_DONT_STRDUP_VAL);
    }

    return 0;
}