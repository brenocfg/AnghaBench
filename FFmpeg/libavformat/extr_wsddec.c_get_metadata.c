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
struct TYPE_3__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char const* const,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (scalar_t__*) ; 
 scalar_t__* av_malloc (unsigned int const) ; 
 unsigned int const avio_read (int /*<<< orphan*/ ,scalar_t__*,unsigned int const) ; 
 scalar_t__ empty_string (scalar_t__*,unsigned int const) ; 

__attribute__((used)) static int get_metadata(AVFormatContext *s, const char *const tag, const unsigned size)
{
    uint8_t *buf;
    if (!(size + 1))
        return AVERROR(ENOMEM);

    buf = av_malloc(size + 1);
    if (!buf)
        return AVERROR(ENOMEM);

    if (avio_read(s->pb, buf, size) != size) {
        av_free(buf);
        return AVERROR(EIO);
    }

    if (empty_string(buf, size)) {
        av_free(buf);
        return 0;
    }

    buf[size] = 0;
    av_dict_set(&s->metadata, tag, buf, AV_DICT_DONT_STRDUP_VAL);
    return 0;
}