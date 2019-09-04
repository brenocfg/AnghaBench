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
typedef  int uint8_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  ID3v2ExtraMeta ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int ID3v2_HEADER_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int avio_read (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_id3v2_34_metadata_conv ; 
 int /*<<< orphan*/  ff_id3v2_4_metadata_conv ; 
 int ff_id3v2_match (int*,char const*) ; 
 int /*<<< orphan*/  ff_metadata_conv (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ffio_ensure_seekback (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  id3v2_2_metadata_conv ; 
 int /*<<< orphan*/  id3v2_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  merge_date (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void id3v2_read_internal(AVIOContext *pb, AVDictionary **metadata,
                                AVFormatContext *s, const char *magic,
                                ID3v2ExtraMeta **extra_meta, int64_t max_search_size)
{
    int len, ret;
    uint8_t buf[ID3v2_HEADER_SIZE];
    int found_header;
    int64_t start, off;

    if (max_search_size && max_search_size < ID3v2_HEADER_SIZE)
        return;

    start = avio_tell(pb);
    do {
        /* save the current offset in case there's nothing to read/skip */
        off = avio_tell(pb);
        if (max_search_size && off - start >= max_search_size - ID3v2_HEADER_SIZE) {
            avio_seek(pb, off, SEEK_SET);
            break;
        }

        ret = ffio_ensure_seekback(pb, ID3v2_HEADER_SIZE);
        if (ret >= 0)
            ret = avio_read(pb, buf, ID3v2_HEADER_SIZE);
        if (ret != ID3v2_HEADER_SIZE) {
            avio_seek(pb, off, SEEK_SET);
            break;
        }
        found_header = ff_id3v2_match(buf, magic);
        if (found_header) {
            /* parse ID3v2 header */
            len = ((buf[6] & 0x7f) << 21) |
                  ((buf[7] & 0x7f) << 14) |
                  ((buf[8] & 0x7f) << 7) |
                   (buf[9] & 0x7f);
            id3v2_parse(pb, metadata, s, len, buf[3], buf[5], extra_meta);
        } else {
            avio_seek(pb, off, SEEK_SET);
        }
    } while (found_header);
    ff_metadata_conv(metadata, NULL, ff_id3v2_34_metadata_conv);
    ff_metadata_conv(metadata, NULL, id3v2_2_metadata_conv);
    ff_metadata_conv(metadata, NULL, ff_id3v2_4_metadata_conv);
    merge_date(metadata);
}