#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; } ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  AV_WL32 (char*,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int UINT_MAX ; 
 int av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_malloc (int) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int avi_read_tag(AVFormatContext *s, AVStream *st, uint32_t tag,
                        uint32_t size)
{
    AVIOContext *pb = s->pb;
    char key[5]     = { 0 };
    char *value;

    size += (size & 1);

    if (size == UINT_MAX)
        return AVERROR(EINVAL);
    value = av_malloc(size + 1);
    if (!value)
        return AVERROR(ENOMEM);
    if (avio_read(pb, value, size) != size) {
        av_freep(&value);
        return AVERROR_INVALIDDATA;
    }
    value[size] = 0;

    AV_WL32(key, tag);

    return av_dict_set(st ? &st->metadata : &s->metadata, key, value,
                       AV_DICT_DONT_STRDUP_VAL);
}