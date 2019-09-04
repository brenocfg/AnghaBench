#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ av_dict_set (int /*<<< orphan*/ *,char const*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_get_str16le (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asf_read_metadata(AVFormatContext *s, const char *title, uint16_t len,
                             unsigned char *ch, uint16_t buflen)
{
    AVIOContext *pb = s->pb;

    avio_get_str16le(pb, len, ch, buflen);
    if (ch[0]) {
        if (av_dict_set(&s->metadata, title, ch, 0) < 0)
            av_log(s, AV_LOG_WARNING, "av_dict_set failed.\n");
    }

    return 0;
}