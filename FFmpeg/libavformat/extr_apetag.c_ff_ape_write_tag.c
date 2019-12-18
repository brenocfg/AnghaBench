#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_9__ {char* value; int /*<<< orphan*/  key; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pb; int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int APE_TAG_FLAG_CONTAINS_HEADER ; 
 int APE_TAG_FLAG_IS_HEADER ; 
 int APE_TAG_FOOTER_BYTES ; 
 int APE_TAG_VERSION ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,char**) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_put_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ff_standardize_creation_time (TYPE_1__*) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_is_ascii (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

int ff_ape_write_tag(AVFormatContext *s)
{
    AVDictionaryEntry *e = NULL;
    int size, ret, count = 0;
    AVIOContext *dyn_bc = NULL;
    uint8_t *dyn_buf = NULL;

    if ((ret = avio_open_dyn_buf(&dyn_bc)) < 0)
        goto end;

    ff_standardize_creation_time(s);
    while ((e = av_dict_get(s->metadata, "", e, AV_DICT_IGNORE_SUFFIX))) {
        int val_len;

        if (!string_is_ascii(e->key)) {
            av_log(s, AV_LOG_WARNING, "Non ASCII keys are not allowed\n");
            continue;
        }

        val_len = strlen(e->value);
        avio_wl32(dyn_bc, val_len);            // value length
        avio_wl32(dyn_bc, 0);                  // item flags
        avio_put_str(dyn_bc, e->key);          // key
        avio_write(dyn_bc, e->value, val_len); // value
        count++;
    }
    if (!count)
        goto end;

    size = avio_close_dyn_buf(dyn_bc, &dyn_buf);
    if (size <= 0)
        goto end;
    size += APE_TAG_FOOTER_BYTES;

    // header
    avio_write(s->pb, "APETAGEX", 8);   // id
    avio_wl32(s->pb, APE_TAG_VERSION);  // version
    avio_wl32(s->pb, size);
    avio_wl32(s->pb, count);

    // flags
    avio_wl32(s->pb, APE_TAG_FLAG_CONTAINS_HEADER | APE_TAG_FLAG_IS_HEADER);
    ffio_fill(s->pb, 0, 8);             // reserved

    avio_write(s->pb, dyn_buf, size - APE_TAG_FOOTER_BYTES);

    // footer
    avio_write(s->pb, "APETAGEX", 8);   // id
    avio_wl32(s->pb, APE_TAG_VERSION);  // version
    avio_wl32(s->pb, size);             // size
    avio_wl32(s->pb, count);            // tag count

    // flags
    avio_wl32(s->pb, APE_TAG_FLAG_CONTAINS_HEADER);
    ffio_fill(s->pb, 0, 8);             // reserved

end:
    if (dyn_bc && !dyn_buf)
        avio_close_dyn_buf(dyn_bc, &dyn_buf);
    av_freep(&dyn_buf);

    return ret;
}