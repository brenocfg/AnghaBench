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
typedef  char const uint8_t ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AV_DICT_DONT_OVERWRITE ; 
 int AV_DICT_DONT_STRDUP_KEY ; 
 int AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 unsigned int ID3v1_GENRE_MAX ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char const*,char const*,int) ; 
 int /*<<< orphan*/  av_freep (char const**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 char* av_strdup (int /*<<< orphan*/ ) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 scalar_t__ decode_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const**,int*) ; 
 int /*<<< orphan*/ * ff_id3v1_genre_str ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void read_ttag(AVFormatContext *s, AVIOContext *pb, int taglen,
                      AVDictionary **metadata, const char *key)
{
    uint8_t *dst;
    int encoding, dict_flags = AV_DICT_DONT_OVERWRITE | AV_DICT_DONT_STRDUP_VAL;
    unsigned genre;

    if (taglen < 1)
        return;

    encoding = avio_r8(pb);
    taglen--; /* account for encoding type byte */

    if (decode_str(s, pb, encoding, &dst, &taglen) < 0) {
        av_log(s, AV_LOG_ERROR, "Error reading frame %s, skipped\n", key);
        return;
    }

    if (!(strcmp(key, "TCON") && strcmp(key, "TCO"))                         &&
        (sscanf(dst, "(%d)", &genre) == 1 || sscanf(dst, "%d", &genre) == 1) &&
        genre <= ID3v1_GENRE_MAX) {
        av_freep(&dst);
        dst = av_strdup(ff_id3v1_genre_str[genre]);
    } else if (!(strcmp(key, "TXXX") && strcmp(key, "TXX"))) {
        /* dst now contains the key, need to get value */
        key = dst;
        if (decode_str(s, pb, encoding, &dst, &taglen) < 0) {
            av_log(s, AV_LOG_ERROR, "Error reading frame %s, skipped\n", key);
            av_freep(&key);
            return;
        }
        dict_flags |= AV_DICT_DONT_STRDUP_KEY;
    } else if (!*dst)
        av_freep(&dst);

    if (dst)
        av_dict_set(metadata, key, dst, dict_flags);
}