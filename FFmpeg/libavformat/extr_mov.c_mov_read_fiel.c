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
typedef  enum AVFieldOrder { ____Placeholder_AVFieldOrder } AVFieldOrder ;
struct TYPE_12__ {int nb_streams; TYPE_4__** streams; } ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_10__ {int size; } ;
struct TYPE_9__ {TYPE_7__* fc; } ;
struct TYPE_8__ {int field_order; } ;
typedef  TYPE_2__ MOVContext ;
typedef  TYPE_3__ MOVAtom ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_FIELD_BB ; 
 int AV_FIELD_BT ; 
 int AV_FIELD_PROGRESSIVE ; 
 int AV_FIELD_TB ; 
 int AV_FIELD_TT ; 
 int AV_FIELD_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int avio_rb16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_read_fiel(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    unsigned mov_field_order;
    enum AVFieldOrder decoded_field_order = AV_FIELD_UNKNOWN;

    if (c->fc->nb_streams < 1) // will happen with jp2 files
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];
    if (atom.size < 2)
        return AVERROR_INVALIDDATA;
    mov_field_order = avio_rb16(pb);
    if ((mov_field_order & 0xFF00) == 0x0100)
        decoded_field_order = AV_FIELD_PROGRESSIVE;
    else if ((mov_field_order & 0xFF00) == 0x0200) {
        switch (mov_field_order & 0xFF) {
        case 0x01: decoded_field_order = AV_FIELD_TT;
                   break;
        case 0x06: decoded_field_order = AV_FIELD_BB;
                   break;
        case 0x09: decoded_field_order = AV_FIELD_TB;
                   break;
        case 0x0E: decoded_field_order = AV_FIELD_BT;
                   break;
        }
    }
    if (decoded_field_order == AV_FIELD_UNKNOWN && mov_field_order) {
        av_log(c->fc, AV_LOG_ERROR, "Unknown MOV field order 0x%04x\n", mov_field_order);
    }
    st->codecpar->field_order = decoded_field_order;

    return 0;
}