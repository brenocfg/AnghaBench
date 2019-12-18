#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int int64_t ;
struct TYPE_12__ {int nb_streams; TYPE_4__** streams; } ;
struct TYPE_11__ {int /*<<< orphan*/  metadata; TYPE_1__* codecpar; } ;
struct TYPE_10__ {int size; } ;
struct TYPE_9__ {scalar_t__ trak_index; int found_hdlr_mdta; int /*<<< orphan*/  isom; TYPE_7__* fc; } ;
struct TYPE_8__ {int /*<<< orphan*/  codec_type; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ MOVContext ;
typedef  TYPE_3__ MOVAtom ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_MP2 ; 
 int /*<<< orphan*/  AV_DICT_DONT_OVERWRITE ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_fourcc2str (scalar_t__) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* av_malloc (int) ; 
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ *) ; 
 int ffio_read_size (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int mov_read_hdlr(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    uint32_t type;
    uint32_t ctype;
    int64_t title_size;
    char *title_str;
    int ret;

    avio_r8(pb); /* version */
    avio_rb24(pb); /* flags */

    /* component type */
    ctype = avio_rl32(pb);
    type = avio_rl32(pb); /* component subtype */

    av_log(c->fc, AV_LOG_TRACE, "ctype=%s\n", av_fourcc2str(ctype));
    av_log(c->fc, AV_LOG_TRACE, "stype=%s\n", av_fourcc2str(type));

    if (c->trak_index < 0) {  // meta not inside a trak
        if (type == MKTAG('m','d','t','a')) {
            c->found_hdlr_mdta = 1;
        }
        return 0;
    }

    st = c->fc->streams[c->fc->nb_streams-1];

    if     (type == MKTAG('v','i','d','e'))
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    else if (type == MKTAG('s','o','u','n'))
        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    else if (type == MKTAG('m','1','a',' '))
        st->codecpar->codec_id = AV_CODEC_ID_MP2;
    else if ((type == MKTAG('s','u','b','p')) || (type == MKTAG('c','l','c','p')))
        st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;

    avio_rb32(pb); /* component  manufacture */
    avio_rb32(pb); /* component flags */
    avio_rb32(pb); /* component flags mask */

    title_size = atom.size - 24;
    if (title_size > 0) {
        if (title_size > FFMIN(INT_MAX, SIZE_MAX-1))
            return AVERROR_INVALIDDATA;
        title_str = av_malloc(title_size + 1); /* Add null terminator */
        if (!title_str)
            return AVERROR(ENOMEM);

        ret = ffio_read_size(pb, title_str, title_size);
        if (ret < 0) {
            av_freep(&title_str);
            return ret;
        }
        title_str[title_size] = 0;
        if (title_str[0]) {
            int off = (!c->isom && title_str[0] == title_size - 1);
            // flag added so as to not set stream handler name if already set from mdia->hdlr
            av_dict_set(&st->metadata, "handler_name", title_str + off, AV_DICT_DONT_OVERWRITE);
        }
        av_freep(&title_str);
    }

    return 0;
}