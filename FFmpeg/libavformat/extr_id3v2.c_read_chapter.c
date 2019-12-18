#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* tag; struct TYPE_7__* next; TYPE_1__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  meta; void* end; void* start; int /*<<< orphan*/  element_id; } ;
typedef  TYPE_1__ ID3v2ExtraMetaCHAP ;
typedef  TYPE_2__ ID3v2ExtraMeta ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 void* av_mallocz (int) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ decode_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ff_id3v2_34_metadata_conv ; 
 int /*<<< orphan*/  ff_id3v2_4_metadata_conv ; 
 int /*<<< orphan*/  ff_metadata_conv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_chapter (TYPE_1__*) ; 
 int /*<<< orphan*/  read_ttag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void read_chapter(AVFormatContext *s, AVIOContext *pb, int len, const char *ttag, ID3v2ExtraMeta **extra_meta, int isv34)
{
    int taglen;
    char tag[5];
    ID3v2ExtraMeta *new_extra = NULL;
    ID3v2ExtraMetaCHAP *chap  = NULL;

    new_extra = av_mallocz(sizeof(*new_extra));
    chap      = av_mallocz(sizeof(*chap));

    if (!new_extra || !chap)
        goto fail;

    if (decode_str(s, pb, 0, &chap->element_id, &len) < 0)
        goto fail;

    if (len < 16)
        goto fail;

    chap->start = avio_rb32(pb);
    chap->end   = avio_rb32(pb);
    avio_skip(pb, 8);

    len -= 16;
    while (len > 10) {
        if (avio_read(pb, tag, 4) < 4)
            goto fail;
        tag[4] = 0;
        taglen = avio_rb32(pb);
        avio_skip(pb, 2);
        len -= 10;
        if (taglen < 0 || taglen > len)
            goto fail;
        if (tag[0] == 'T')
            read_ttag(s, pb, taglen, &chap->meta, tag);
        else
            avio_skip(pb, taglen);
        len -= taglen;
    }

    ff_metadata_conv(&chap->meta, NULL, ff_id3v2_34_metadata_conv);
    ff_metadata_conv(&chap->meta, NULL, ff_id3v2_4_metadata_conv);

    new_extra->tag  = "CHAP";
    new_extra->data = chap;
    new_extra->next = *extra_meta;
    *extra_meta     = new_extra;

    return;

fail:
    if (chap)
        free_chapter(chap);
    av_freep(&new_extra);
}