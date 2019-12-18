#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mimetype ;
typedef  scalar_t__ int64_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_12__ {char* data; } ;
struct TYPE_11__ {scalar_t__ id; int /*<<< orphan*/  str; } ;
struct TYPE_10__ {char* tag; struct TYPE_10__* next; TYPE_1__* data; } ;
struct TYPE_9__ {int id; int /*<<< orphan*/  description; TYPE_8__* buf; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ID3v2ExtraMetaAPIC ;
typedef  TYPE_2__ ID3v2ExtraMeta ;
typedef  TYPE_3__ CodecMime ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_8__* av_buffer_alloc (scalar_t__) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  av_strncasecmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ avio_get_str (int /*<<< orphan*/ *,int,char*,int) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ decode_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 TYPE_3__* ff_id3v2_mime_tags ; 
 int /*<<< orphan*/ * ff_id3v2_picture_types ; 
 int /*<<< orphan*/  free_apic (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rstrip_spaces (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_apic(AVFormatContext *s, AVIOContext *pb, int taglen,
                      const char *tag, ID3v2ExtraMeta **extra_meta,
                      int isv34)
{
    int enc, pic_type;
    char mimetype[64] = {0};
    const CodecMime *mime     = ff_id3v2_mime_tags;
    enum AVCodecID id         = AV_CODEC_ID_NONE;
    ID3v2ExtraMetaAPIC *apic  = NULL;
    ID3v2ExtraMeta *new_extra = NULL;
    int64_t end               = avio_tell(pb) + taglen;

    if (taglen <= 4 || (!isv34 && taglen <= 6))
        goto fail;

    new_extra = av_mallocz(sizeof(*new_extra));
    apic      = av_mallocz(sizeof(*apic));
    if (!new_extra || !apic)
        goto fail;

    enc = avio_r8(pb);
    taglen--;

    /* mimetype */
    if (isv34) {
        taglen -= avio_get_str(pb, taglen, mimetype, sizeof(mimetype));
    } else {
        if (avio_read(pb, mimetype, 3) < 0)
            goto fail;

        mimetype[3] = 0;
        taglen    -= 3;
    }

    while (mime->id != AV_CODEC_ID_NONE) {
        if (!av_strncasecmp(mime->str, mimetype, sizeof(mimetype))) {
            id = mime->id;
            break;
        }
        mime++;
    }
    if (id == AV_CODEC_ID_NONE) {
        av_log(s, AV_LOG_WARNING,
               "Unknown attached picture mimetype: %s, skipping.\n", mimetype);
        goto fail;
    }
    apic->id = id;

    /* picture type */
    pic_type = avio_r8(pb);
    taglen--;
    if (pic_type < 0 || pic_type >= FF_ARRAY_ELEMS(ff_id3v2_picture_types)) {
        av_log(s, AV_LOG_WARNING, "Unknown attached picture type %d.\n",
               pic_type);
        pic_type = 0;
    }
    apic->type = ff_id3v2_picture_types[pic_type];

    /* description and picture data */
    if (decode_str(s, pb, enc, &apic->description, &taglen) < 0) {
        av_log(s, AV_LOG_ERROR,
               "Error decoding attached picture description.\n");
        goto fail;
    }

    apic->buf = av_buffer_alloc(taglen + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!apic->buf || !taglen || avio_read(pb, apic->buf->data, taglen) != taglen)
        goto fail;
    memset(apic->buf->data + taglen, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    new_extra->tag  = "APIC";
    new_extra->data = apic;
    new_extra->next = *extra_meta;
    *extra_meta     = new_extra;

    // The description must be unique, and some ID3v2 tag writers add spaces
    // to write several APIC entries with the same description.
    rstrip_spaces(apic->description);

    return;

fail:
    if (apic)
        free_apic(apic);
    av_freep(&new_extra);
    avio_seek(pb, end, SEEK_SET);
}