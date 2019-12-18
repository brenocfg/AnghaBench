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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_malloc (size_t) ; 
 int avio_get_str16be (int /*<<< orphan*/ *,int,char*,size_t) ; 
 int avio_get_str16le (int /*<<< orphan*/ *,int,char*,size_t) ; 

__attribute__((used)) static inline int mxf_read_utf16_string(AVIOContext *pb, int size, char** str, int be)
{
    int ret;
    size_t buf_size;

    if (size < 0 || size > INT_MAX/2)
        return AVERROR(EINVAL);

    buf_size = size + size / 2 + 1;
    *str = av_malloc(buf_size);
    if (!*str)
        return AVERROR(ENOMEM);

    if (be)
        ret = avio_get_str16be(pb, size, *str, buf_size);
    else
        ret = avio_get_str16le(pb, size, *str, buf_size);

    if (ret < 0) {
        av_freep(str);
        return ret;
    }

    return ret;
}