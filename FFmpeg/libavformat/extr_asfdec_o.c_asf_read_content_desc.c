#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  GUIDParseTable ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ASFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  align_position (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asf_read_metadata (TYPE_1__*,char const* const,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asf_read_content_desc(AVFormatContext *s, const GUIDParseTable *g)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    int i;
    static const char *const titles[] =
    { "Title", "Author", "Copyright", "Description", "Rate" };
    uint16_t len[5], buflen[5] = { 0 };
    uint8_t *ch;
    uint64_t size = avio_rl64(pb);

    for (i = 0; i < 5; i++) {
        len[i]  = avio_rl16(pb);
        // utf8 string should be <= 2 * utf16 string, extra byte for the terminator
        buflen[i]  = 2 * len[i] + 1;
    }

    for (i = 0; i < 5; i++) {
        ch = av_malloc(buflen[i]);
        if (!ch)
            return(AVERROR(ENOMEM));
        asf_read_metadata(s, titles[i], len[i], ch, buflen[i]);
        av_freep(&ch);
    }
    align_position(pb, asf->offset, size);

    return 0;
}