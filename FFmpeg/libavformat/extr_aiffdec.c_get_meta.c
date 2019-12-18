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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  pb; int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char const*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (scalar_t__*) ; 
 scalar_t__* av_malloc (int) ; 
 int avio_read (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void get_meta(AVFormatContext *s, const char *key, int size)
{
    uint8_t *str = av_malloc(size+1);

    if (str) {
        int res = avio_read(s->pb, str, size);
        if (res < 0){
            av_free(str);
            return;
        }
        size -= res;
        str[res] = 0;
        av_dict_set(&s->metadata, key, str, AV_DICT_DONT_STRDUP_VAL);
    }

    avio_skip(s->pb, size);
}