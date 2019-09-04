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
typedef  int int8_t ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  auto_sep (int,char const*,int,int) ; 
 int av_bprint_finalize (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char const*,char*,int /*<<< orphan*/ ) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 

int ff_tadd_bytes_metadata(int count, const char *name, const char *sep,
                           GetByteContext *gb, int le, int is_signed, AVDictionary **metadata)
{
    AVBPrint bp;
    char *ap;
    int i;

    if (count >= INT_MAX / sizeof(int8_t) || count < 0)
        return AVERROR_INVALIDDATA;
    if (bytestream2_get_bytes_left(gb) < count * sizeof(int8_t))
        return AVERROR_INVALIDDATA;

    av_bprint_init(&bp, 10 * count, AV_BPRINT_SIZE_UNLIMITED);

    for (i = 0; i < count; i++) {
        int v = is_signed ? (int8_t)bytestream2_get_byte(gb) :  bytestream2_get_byte(gb);
        av_bprintf(&bp, "%s%3i", auto_sep(count, sep, i, 16), v);
    }

    if ((i = av_bprint_finalize(&bp, &ap))) {
        return i;
    }
    if (!ap) {
        return AVERROR(ENOMEM);
    }

    av_dict_set(metadata, name, ap, AV_DICT_DONT_STRDUP_VAL);

    return 0;
}