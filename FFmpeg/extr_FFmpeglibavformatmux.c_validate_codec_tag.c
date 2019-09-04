#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_12__ {scalar_t__ id; scalar_t__ tag; } ;
struct TYPE_11__ {scalar_t__ strict_std_compliance; TYPE_1__* oformat; } ;
struct TYPE_10__ {TYPE_2__* codecpar; } ;
struct TYPE_9__ {scalar_t__ codec_tag; int codec_id; } ;
struct TYPE_8__ {TYPE_5__** codec_tag; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecTag ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 scalar_t__ FF_COMPLIANCE_NORMAL ; 
 scalar_t__ avpriv_toupper4 (scalar_t__) ; 

__attribute__((used)) static int validate_codec_tag(AVFormatContext *s, AVStream *st)
{
    const AVCodecTag *avctag;
    int n;
    enum AVCodecID id = AV_CODEC_ID_NONE;
    int64_t tag  = -1;

    /**
     * Check that tag + id is in the table
     * If neither is in the table -> OK
     * If tag is in the table with another id -> FAIL
     * If id is in the table with another tag -> FAIL unless strict < normal
     */
    for (n = 0; s->oformat->codec_tag[n]; n++) {
        avctag = s->oformat->codec_tag[n];
        while (avctag->id != AV_CODEC_ID_NONE) {
            if (avpriv_toupper4(avctag->tag) == avpriv_toupper4(st->codecpar->codec_tag)) {
                id = avctag->id;
                if (id == st->codecpar->codec_id)
                    return 1;
            }
            if (avctag->id == st->codecpar->codec_id)
                tag = avctag->tag;
            avctag++;
        }
    }
    if (id != AV_CODEC_ID_NONE)
        return 0;
    if (tag >= 0 && (s->strict_std_compliance >= FF_COMPLIANCE_NORMAL))
        return 0;
    return 1;
}