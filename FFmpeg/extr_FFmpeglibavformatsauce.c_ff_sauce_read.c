#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  metadata; TYPE_2__** streams; int /*<<< orphan*/ * pb; } ;
struct TYPE_6__ {TYPE_1__* codecpar; } ;
struct TYPE_5__ {int width; int height; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 char* av_malloc (int) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

int ff_sauce_read(AVFormatContext *avctx, uint64_t *fsize, int *got_width, int get_height)
{
    AVIOContext *pb = avctx->pb;
    char buf[36];
    int datatype, filetype, t1, t2, nb_comments;
    uint64_t start_pos = avio_size(pb) - 128;

    avio_seek(pb, start_pos, SEEK_SET);
    if (avio_read(pb, buf, 7) != 7)
        return -1;
    if (memcmp(buf, "SAUCE00", 7))
        return -1;

#define GET_SAUCE_META(name,size) \
    if (avio_read(pb, buf, size) == size && buf[0]) { \
        buf[size] = 0; \
        av_dict_set(&avctx->metadata, name, buf, 0); \
    }

    GET_SAUCE_META("title",     35)
    GET_SAUCE_META("artist",    20)
    GET_SAUCE_META("publisher", 20)
    GET_SAUCE_META("date",      8)
    avio_skip(pb, 4);
    datatype    = avio_r8(pb);
    filetype    = avio_r8(pb);
    t1          = avio_rl16(pb);
    t2          = avio_rl16(pb);
    nb_comments = avio_r8(pb);
    avio_skip(pb, 1); /* flags */
    avio_skip(pb, 4);
    GET_SAUCE_META("encoder",   22);

    if (got_width && datatype && filetype) {
        if ((datatype == 1 && filetype <=2) || (datatype == 5 && filetype == 255) || datatype == 6) {
            if (t1) {
                avctx->streams[0]->codecpar->width = t1<<3;
                *got_width = 1;
            }
            if (get_height && t2)
                avctx->streams[0]->codecpar->height = t2<<4;
        } else if (datatype == 5) {
            if (filetype) {
                avctx->streams[0]->codecpar->width = (filetype == 1 ? t1 : filetype) << 4;
                *got_width = 1;
            }
            if (get_height && t2)
                avctx->streams[0]->codecpar->height = t2<<4;
        }
    }

    *fsize -= 128;

    if (nb_comments > 0) {
        avio_seek(pb, start_pos - 64*nb_comments - 5, SEEK_SET);
        if (avio_read(pb, buf, 5) == 5 && !memcmp(buf, "COMNT", 5)) {
            int i;
            char *str = av_malloc(65*nb_comments + 1);
            *fsize -= 64*nb_comments + 5;
            if (!str)
                return 0;
            for (i = 0; i < nb_comments; i++) {
                if (avio_read(pb, str + 65*i, 64) != 64)
                    break;
                str[65*i + 64] = '\n';
            }
            str[65*i] = 0;
            av_dict_set(&avctx->metadata, "comment", str, AV_DICT_DONT_STRDUP_VAL);
        }
    }

    return 0;
}