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
struct TYPE_5__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  GUIDParseTable ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ASFContext ;

/* Variables and functions */
 int ASF_BOOL ; 
 int ASF_DWORD ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  align_position (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int /*<<< orphan*/  avio_get_str16le (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl64 (int /*<<< orphan*/ *) ; 
 int process_metadata (TYPE_1__*,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asf_read_ext_content(AVFormatContext *s, const GUIDParseTable *g)
{
    ASFContext *asf  = s->priv_data;
    AVIOContext *pb  = s->pb;
    uint64_t size    = avio_rl64(pb);
    uint16_t nb_desc = avio_rl16(pb);
    int i, ret;

    for (i = 0; i < nb_desc; i++) {
        uint16_t name_len, type, val_len;
        uint8_t *name = NULL;

        name_len = avio_rl16(pb);
        if (!name_len)
            return AVERROR_INVALIDDATA;
        name = av_malloc(name_len);
        if (!name)
            return AVERROR(ENOMEM);
        avio_get_str16le(pb, name_len, name,
                         name_len);
        type    = avio_rl16(pb);
        // BOOL values are 16 bits long in the Metadata Object
        // but 32 bits long in the Extended Content Description Object
        if (type == ASF_BOOL)
            type = ASF_DWORD;
        val_len = avio_rl16(pb);

        ret = process_metadata(s, name, name_len, val_len, type, &s->metadata);
        av_freep(&name);
        if (ret < 0)
            return ret;
    }

    align_position(pb, asf->offset, size);
    return 0;
}