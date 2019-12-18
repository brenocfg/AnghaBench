#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_5__ {int (* io_open ) (TYPE_1__*,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int /*<<< orphan*/  EIO ; 
 int MKTAG (unsigned char,unsigned char,char,char) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int avio_rb64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_fragment(AVFormatContext *s, const char *filename, int64_t *start_ts, int64_t *duration, int64_t *moof_size, int64_t size)
{
    AVIOContext *in;
    int ret;
    uint32_t len;
    if ((ret = s->io_open(s, &in, filename, AVIO_FLAG_READ, NULL)) < 0)
        return ret;
    ret = AVERROR(EIO);
    *moof_size = avio_rb32(in);
    if (*moof_size < 8 || *moof_size > size)
        goto fail;
    if (avio_rl32(in) != MKTAG('m','o','o','f'))
        goto fail;
    len = avio_rb32(in);
    if (len > *moof_size)
        goto fail;
    if (avio_rl32(in) != MKTAG('m','f','h','d'))
        goto fail;
    avio_seek(in, len - 8, SEEK_CUR);
    avio_rb32(in); /* traf size */
    if (avio_rl32(in) != MKTAG('t','r','a','f'))
        goto fail;
    while (avio_tell(in) < *moof_size) {
        uint32_t len = avio_rb32(in);
        uint32_t tag = avio_rl32(in);
        int64_t end = avio_tell(in) + len - 8;
        if (len < 8 || len >= *moof_size)
            goto fail;
        if (tag == MKTAG('u','u','i','d')) {
            static const uint8_t tfxd[] = {
                0x6d, 0x1d, 0x9b, 0x05, 0x42, 0xd5, 0x44, 0xe6,
                0x80, 0xe2, 0x14, 0x1d, 0xaf, 0xf7, 0x57, 0xb2
            };
            uint8_t uuid[16];
            avio_read(in, uuid, 16);
            if (!memcmp(uuid, tfxd, 16) && len >= 8 + 16 + 4 + 16) {
                avio_seek(in, 4, SEEK_CUR);
                *start_ts = avio_rb64(in);
                *duration = avio_rb64(in);
                ret = 0;
                break;
            }
        }
        avio_seek(in, end, SEEK_SET);
    }
fail:
    ff_format_io_close(s, &in);
    return ret;
}