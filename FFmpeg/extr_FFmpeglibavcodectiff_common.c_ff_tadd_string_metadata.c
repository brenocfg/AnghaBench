#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char const*,char*,int /*<<< orphan*/ ) ; 
 char* av_malloc (int) ; 
 int /*<<< orphan*/  bytestream2_get_bufferu (int /*<<< orphan*/ *,char*,int) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 

int ff_tadd_string_metadata(int count, const char *name,
                            GetByteContext *gb, int le, AVDictionary **metadata)
{
    char *value;

    if (bytestream2_get_bytes_left(gb) < count || count < 0)
        return AVERROR_INVALIDDATA;

    value = av_malloc(count + 1);
    if (!value)
        return AVERROR(ENOMEM);

    bytestream2_get_bufferu(gb, value, count);
    value[count] = 0;

    av_dict_set(metadata, name, value, AV_DICT_DONT_STRDUP_VAL);
    return 0;
}