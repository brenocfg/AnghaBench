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
struct TYPE_6__ {int nb_chapters; int /*<<< orphan*/  pb; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ ID3v2EncContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ ID3v2_HEADER_SIZE ; 
 int MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 scalar_t__ avio_put_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int write_ctoc(AVFormatContext *s, ID3v2EncContext *id3, int enc)
{
    uint8_t *dyn_buf = NULL;
    AVIOContext *dyn_bc = NULL;
    char name[123];
    int len, ret;

    if (s->nb_chapters == 0)
        return 0;

    if ((ret = avio_open_dyn_buf(&dyn_bc)) < 0)
        goto fail;

    id3->len += avio_put_str(dyn_bc, "toc");
    avio_w8(dyn_bc, 0x03);
    avio_w8(dyn_bc, s->nb_chapters);
    for (int i = 0; i < s->nb_chapters; i++) {
        snprintf(name, 122, "ch%d", i);
        id3->len += avio_put_str(dyn_bc, name);
    }
    len = avio_close_dyn_buf(dyn_bc, &dyn_buf);
    id3->len += 16 + ID3v2_HEADER_SIZE;

    avio_wb32(s->pb, MKBETAG('C', 'T', 'O', 'C'));
    avio_wb32(s->pb, len);
    avio_wb16(s->pb, 0);
    avio_write(s->pb, dyn_buf, len);

fail:
    if (dyn_bc && !dyn_buf)
        avio_close_dyn_buf(dyn_bc, &dyn_buf);
    av_freep(&dyn_buf);

    return ret;
}