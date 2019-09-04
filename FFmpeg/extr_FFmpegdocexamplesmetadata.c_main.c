#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* key; char* value; } ;
struct TYPE_8__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_1__**) ; 
 int avformat_find_stream_info (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int avformat_open_input (TYPE_1__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

int main (int argc, char **argv)
{
    AVFormatContext *fmt_ctx = NULL;
    AVDictionaryEntry *tag = NULL;
    int ret;

    if (argc != 2) {
        printf("usage: %s <input_file>\n"
               "example program to demonstrate the use of the libavformat metadata API.\n"
               "\n", argv[0]);
        return 1;
    }

    if ((ret = avformat_open_input(&fmt_ctx, argv[1], NULL, NULL)))
        return ret;

    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return ret;
    }

    while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
        printf("%s=%s\n", tag->key, tag->value);

    avformat_close_input(&fmt_ctx);
    return 0;
}