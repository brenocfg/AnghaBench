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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 char* av_asprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ decode_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char**,int*) ; 

__attribute__((used)) static void read_uslt(AVFormatContext *s, AVIOContext *pb, int taglen,
                      AVDictionary **metadata)
{
    uint8_t lang[4];
    uint8_t *descriptor = NULL; // 'Content descriptor'
    uint8_t *text = NULL;
    char *key = NULL;
    int encoding;
    int ok = 0;

    if (taglen < 1)
        goto error;

    encoding = avio_r8(pb);
    taglen--;

    if (avio_read(pb, lang, 3) < 3)
        goto error;
    lang[3] = '\0';
    taglen -= 3;

    if (decode_str(s, pb, encoding, &descriptor, &taglen) < 0)
        goto error;

    if (decode_str(s, pb, encoding, &text, &taglen) < 0)
        goto error;

    // FFmpeg does not support hierarchical metadata, so concatenate the keys.
    key = av_asprintf("lyrics-%s%s%s", descriptor[0] ? (char *)descriptor : "",
                                       descriptor[0] ? "-" : "",
                                       lang);
    if (!key)
        goto error;

    av_dict_set(metadata, key, text, 0);

    ok = 1;
error:
    if (!ok)
        av_log(s, AV_LOG_ERROR, "Error reading lyrics, skipped\n");
    av_free(descriptor);
    av_free(text);
    av_free(key);
}