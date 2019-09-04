#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int nreslevels; } ;
struct TYPE_13__ {int /*<<< orphan*/  nguardbits; scalar_t__ expn; } ;
struct TYPE_14__ {int ncomponents; int /*<<< orphan*/  avctx; TYPE_2__* tile; TYPE_4__ qntsty; TYPE_6__ codsty; } ;
struct TYPE_12__ {int num_precincts_x; int num_precincts_y; } ;
struct TYPE_11__ {TYPE_1__* comp; } ;
struct TYPE_10__ {TYPE_3__* reslevel; } ;
typedef  int /*<<< orphan*/  Jpeg2000Tile ;
typedef  TYPE_3__ Jpeg2000ResLevel ;
typedef  TYPE_4__ Jpeg2000QuantStyle ;
typedef  TYPE_5__ Jpeg2000EncoderContext ;
typedef  TYPE_6__ Jpeg2000CodingStyle ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int encode_packet (TYPE_5__*,TYPE_3__*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int encode_packets(Jpeg2000EncoderContext *s, Jpeg2000Tile *tile, int tileno)
{
    int compno, reslevelno, ret;
    Jpeg2000CodingStyle *codsty = &s->codsty;
    Jpeg2000QuantStyle  *qntsty = &s->qntsty;

    av_log(s->avctx, AV_LOG_DEBUG, "tier2\n");
    // lay-rlevel-comp-pos progression
    for (reslevelno = 0; reslevelno < codsty->nreslevels; reslevelno++){
        for (compno = 0; compno < s->ncomponents; compno++){
            int precno;
            Jpeg2000ResLevel *reslevel = s->tile[tileno].comp[compno].reslevel + reslevelno;
            for (precno = 0; precno < reslevel->num_precincts_x * reslevel->num_precincts_y; precno++){
                if ((ret = encode_packet(s, reslevel, precno, qntsty->expn + (reslevelno ? 3*reslevelno-2 : 0),
                              qntsty->nguardbits)) < 0)
                    return ret;
            }
        }
    }
    av_log(s->avctx, AV_LOG_DEBUG, "after tier2\n");
    return 0;
}