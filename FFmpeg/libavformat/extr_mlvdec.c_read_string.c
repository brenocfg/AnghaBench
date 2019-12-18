#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_malloc (unsigned int) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void read_string(AVFormatContext *avctx, AVIOContext *pb, const char *tag, unsigned size)
{
    char * value = av_malloc(size + 1);
    if (!value) {
        avio_skip(pb, size);
        return;
    }

    avio_read(pb, value, size);
    if (!value[0]) {
        av_free(value);
        return;
    }

    value[size] = 0;
    av_dict_set(&avctx->metadata, tag, value, AV_DICT_DONT_STRDUP_VAL);
}