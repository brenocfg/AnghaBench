#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  long long uint8_t ;
struct TYPE_18__ {int nreslevels; } ;
struct TYPE_17__ {int** coord_o; int /*<<< orphan*/  reslevel; } ;
struct TYPE_16__ {int* cdx; int* cdy; int /*<<< orphan*/  avctx; } ;
struct TYPE_15__ {int /*<<< orphan*/  nguardbits; int /*<<< orphan*/  expn; } ;
struct TYPE_14__ {int num_precincts_x; int num_precincts_y; long long log2_prec_width; long long log2_prec_height; } ;
struct TYPE_13__ {int** coord; TYPE_3__* qntsty; TYPE_6__* codsty; TYPE_5__* comp; } ;
typedef  TYPE_1__ Jpeg2000Tile ;
typedef  TYPE_2__ Jpeg2000ResLevel ;
typedef  TYPE_3__ Jpeg2000QuantStyle ;
typedef  TYPE_4__ Jpeg2000DecoderContext ;
typedef  TYPE_5__ Jpeg2000Component ;
typedef  TYPE_6__ Jpeg2000CodingStyle ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FFMIN (int,int) ; 
#define  JPEG2000_PGOD_CPRL 132 
#define  JPEG2000_PGOD_LRCP 131 
#define  JPEG2000_PGOD_PCRL 130 
#define  JPEG2000_PGOD_RLCP 129 
#define  JPEG2000_PGOD_RPCL 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 
 unsigned int ff_jpeg2000_ceildivpow2 (int,long long) ; 
 int jpeg2000_decode_packet (TYPE_4__*,TYPE_1__*,int*,TYPE_6__*,TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jpeg2000_decode_packets_po_iteration(Jpeg2000DecoderContext *s, Jpeg2000Tile *tile,
                                             int RSpoc, int CSpoc,
                                             int LYEpoc, int REpoc, int CEpoc,
                                             int Ppoc, int *tp_index)
{
    int ret = 0;
    int layno, reslevelno, compno, precno, ok_reslevel;
    int x, y;
    int step_x, step_y;

    switch (Ppoc) {
    case JPEG2000_PGOD_RLCP:
        av_log(s->avctx, AV_LOG_DEBUG, "Progression order RLCP\n");
        ok_reslevel = 1;
        for (reslevelno = RSpoc; ok_reslevel && reslevelno < REpoc; reslevelno++) {
            ok_reslevel = 0;
            for (layno = 0; layno < LYEpoc; layno++) {
                for (compno = CSpoc; compno < CEpoc; compno++) {
                    Jpeg2000CodingStyle *codsty = tile->codsty + compno;
                    Jpeg2000QuantStyle *qntsty  = tile->qntsty + compno;
                    if (reslevelno < codsty->nreslevels) {
                        Jpeg2000ResLevel *rlevel = tile->comp[compno].reslevel +
                                                reslevelno;
                        ok_reslevel = 1;
                        for (precno = 0; precno < rlevel->num_precincts_x * rlevel->num_precincts_y; precno++)
                            if ((ret = jpeg2000_decode_packet(s, tile, tp_index,
                                                              codsty, rlevel,
                                                              precno, layno,
                                                              qntsty->expn + (reslevelno ? 3 * (reslevelno - 1) + 1 : 0),
                                                              qntsty->nguardbits)) < 0)
                                return ret;
                    }
                }
            }
        }
        break;

    case JPEG2000_PGOD_LRCP:
        av_log(s->avctx, AV_LOG_DEBUG, "Progression order LRCP\n");
        for (layno = 0; layno < LYEpoc; layno++) {
            ok_reslevel = 1;
            for (reslevelno = RSpoc; ok_reslevel && reslevelno < REpoc; reslevelno++) {
                ok_reslevel = 0;
                for (compno = CSpoc; compno < CEpoc; compno++) {
                    Jpeg2000CodingStyle *codsty = tile->codsty + compno;
                    Jpeg2000QuantStyle *qntsty  = tile->qntsty + compno;
                    if (reslevelno < codsty->nreslevels) {
                        Jpeg2000ResLevel *rlevel = tile->comp[compno].reslevel +
                                                reslevelno;
                        ok_reslevel = 1;
                        for (precno = 0; precno < rlevel->num_precincts_x * rlevel->num_precincts_y; precno++)
                            if ((ret = jpeg2000_decode_packet(s, tile, tp_index,
                                                              codsty, rlevel,
                                                              precno, layno,
                                                              qntsty->expn + (reslevelno ? 3 * (reslevelno - 1) + 1 : 0),
                                                              qntsty->nguardbits)) < 0)
                                return ret;
                    }
                }
            }
        }
        break;

    case JPEG2000_PGOD_CPRL:
        av_log(s->avctx, AV_LOG_DEBUG, "Progression order CPRL\n");
        for (compno = CSpoc; compno < CEpoc; compno++) {
            Jpeg2000Component *comp     = tile->comp + compno;
            Jpeg2000CodingStyle *codsty = tile->codsty + compno;
            Jpeg2000QuantStyle *qntsty  = tile->qntsty + compno;
            step_x = 32;
            step_y = 32;

            if (RSpoc >= FFMIN(codsty->nreslevels, REpoc))
                continue;

            for (reslevelno = RSpoc; reslevelno < FFMIN(codsty->nreslevels, REpoc); reslevelno++) {
                uint8_t reducedresno = codsty->nreslevels - 1 -reslevelno; //  ==> N_L - r
                Jpeg2000ResLevel *rlevel = comp->reslevel + reslevelno;
                step_x = FFMIN(step_x, rlevel->log2_prec_width  + reducedresno);
                step_y = FFMIN(step_y, rlevel->log2_prec_height + reducedresno);
            }
            if (step_x >= 31 || step_y >= 31){
                avpriv_request_sample(s->avctx, "CPRL with large step");
                return AVERROR_PATCHWELCOME;
            }
            step_x = 1<<step_x;
            step_y = 1<<step_y;

            for (y = tile->coord[1][0]; y < tile->coord[1][1]; y = (y/step_y + 1)*step_y) {
                for (x = tile->coord[0][0]; x < tile->coord[0][1]; x = (x/step_x + 1)*step_x) {
                    for (reslevelno = RSpoc; reslevelno < FFMIN(codsty->nreslevels, REpoc); reslevelno++) {
                        unsigned prcx, prcy;
                        uint8_t reducedresno = codsty->nreslevels - 1 -reslevelno; //  ==> N_L - r
                        Jpeg2000ResLevel *rlevel = comp->reslevel + reslevelno;
                        int xc = x / s->cdx[compno];
                        int yc = y / s->cdy[compno];

                        if (yc % (1LL << (rlevel->log2_prec_height + reducedresno)) && y != tile->coord[1][0]) //FIXME this is a subset of the check
                            continue;

                        if (xc % (1LL << (rlevel->log2_prec_width + reducedresno)) && x != tile->coord[0][0]) //FIXME this is a subset of the check
                            continue;

                        // check if a precinct exists
                        prcx   = ff_jpeg2000_ceildivpow2(xc, reducedresno) >> rlevel->log2_prec_width;
                        prcy   = ff_jpeg2000_ceildivpow2(yc, reducedresno) >> rlevel->log2_prec_height;
                        prcx  -= ff_jpeg2000_ceildivpow2(comp->coord_o[0][0], reducedresno) >> rlevel->log2_prec_width;
                        prcy  -= ff_jpeg2000_ceildivpow2(comp->coord_o[1][0], reducedresno) >> rlevel->log2_prec_height;

                        precno = prcx + rlevel->num_precincts_x * prcy;

                        if (prcx >= rlevel->num_precincts_x || prcy >= rlevel->num_precincts_y) {
                            av_log(s->avctx, AV_LOG_WARNING, "prc %d %d outside limits %d %d\n",
                                   prcx, prcy, rlevel->num_precincts_x, rlevel->num_precincts_y);
                            continue;
                        }

                        for (layno = 0; layno < LYEpoc; layno++) {
                            if ((ret = jpeg2000_decode_packet(s, tile, tp_index, codsty, rlevel,
                                                              precno, layno,
                                                              qntsty->expn + (reslevelno ? 3 * (reslevelno - 1) + 1 : 0),
                                                              qntsty->nguardbits)) < 0)
                                return ret;
                        }
                    }
                }
            }
        }
        break;

    case JPEG2000_PGOD_RPCL:
        av_log(s->avctx, AV_LOG_WARNING, "Progression order RPCL\n");
        ok_reslevel = 1;
        for (reslevelno = RSpoc; ok_reslevel && reslevelno < REpoc; reslevelno++) {
            ok_reslevel = 0;
            step_x = 30;
            step_y = 30;
            for (compno = CSpoc; compno < CEpoc; compno++) {
                Jpeg2000Component *comp     = tile->comp + compno;
                Jpeg2000CodingStyle *codsty = tile->codsty + compno;

                if (reslevelno < codsty->nreslevels) {
                    uint8_t reducedresno = codsty->nreslevels - 1 -reslevelno; //  ==> N_L - r
                    Jpeg2000ResLevel *rlevel = comp->reslevel + reslevelno;
                    step_x = FFMIN(step_x, rlevel->log2_prec_width  + reducedresno);
                    step_y = FFMIN(step_y, rlevel->log2_prec_height + reducedresno);
                }
            }
            step_x = 1<<step_x;
            step_y = 1<<step_y;

            for (y = tile->coord[1][0]; y < tile->coord[1][1]; y = (y/step_y + 1)*step_y) {
                for (x = tile->coord[0][0]; x < tile->coord[0][1]; x = (x/step_x + 1)*step_x) {
                    for (compno = CSpoc; compno < CEpoc; compno++) {
                        Jpeg2000Component *comp     = tile->comp + compno;
                        Jpeg2000CodingStyle *codsty = tile->codsty + compno;
                        Jpeg2000QuantStyle *qntsty  = tile->qntsty + compno;
                        uint8_t reducedresno = codsty->nreslevels - 1 -reslevelno; //  ==> N_L - r
                        Jpeg2000ResLevel *rlevel = comp->reslevel + reslevelno;
                        unsigned prcx, prcy;

                        int xc = x / s->cdx[compno];
                        int yc = y / s->cdy[compno];

                        if (reslevelno >= codsty->nreslevels)
                            continue;

                        if (yc % (1LL << (rlevel->log2_prec_height + reducedresno)) && y != tile->coord[1][0]) //FIXME this is a subset of the check
                            continue;

                        if (xc % (1LL << (rlevel->log2_prec_width + reducedresno)) && x != tile->coord[0][0]) //FIXME this is a subset of the check
                            continue;

                        // check if a precinct exists
                        prcx   = ff_jpeg2000_ceildivpow2(xc, reducedresno) >> rlevel->log2_prec_width;
                        prcy   = ff_jpeg2000_ceildivpow2(yc, reducedresno) >> rlevel->log2_prec_height;
                        prcx  -= ff_jpeg2000_ceildivpow2(comp->coord_o[0][0], reducedresno) >> rlevel->log2_prec_width;
                        prcy  -= ff_jpeg2000_ceildivpow2(comp->coord_o[1][0], reducedresno) >> rlevel->log2_prec_height;

                        precno = prcx + rlevel->num_precincts_x * prcy;

                        ok_reslevel = 1;
                        if (prcx >= rlevel->num_precincts_x || prcy >= rlevel->num_precincts_y) {
                            av_log(s->avctx, AV_LOG_WARNING, "prc %d %d outside limits %d %d\n",
                                   prcx, prcy, rlevel->num_precincts_x, rlevel->num_precincts_y);
                            continue;
                        }

                            for (layno = 0; layno < LYEpoc; layno++) {
                                if ((ret = jpeg2000_decode_packet(s, tile, tp_index,
                                                                codsty, rlevel,
                                                                precno, layno,
                                                                qntsty->expn + (reslevelno ? 3 * (reslevelno - 1) + 1 : 0),
                                                                qntsty->nguardbits)) < 0)
                                    return ret;
                            }
                    }
                }
            }
        }
        break;

    case JPEG2000_PGOD_PCRL:
        av_log(s->avctx, AV_LOG_WARNING, "Progression order PCRL\n");
        step_x = 32;
        step_y = 32;
        for (compno = CSpoc; compno < CEpoc; compno++) {
            Jpeg2000Component *comp     = tile->comp + compno;
            Jpeg2000CodingStyle *codsty = tile->codsty + compno;

            for (reslevelno = RSpoc; reslevelno < FFMIN(codsty->nreslevels, REpoc); reslevelno++) {
                uint8_t reducedresno = codsty->nreslevels - 1 -reslevelno; //  ==> N_L - r
                Jpeg2000ResLevel *rlevel = comp->reslevel + reslevelno;
                step_x = FFMIN(step_x, rlevel->log2_prec_width  + reducedresno);
                step_y = FFMIN(step_y, rlevel->log2_prec_height + reducedresno);
            }
        }
        if (step_x >= 31 || step_y >= 31){
            avpriv_request_sample(s->avctx, "PCRL with large step");
            return AVERROR_PATCHWELCOME;
        }
        step_x = 1<<step_x;
        step_y = 1<<step_y;

        for (y = tile->coord[1][0]; y < tile->coord[1][1]; y = (y/step_y + 1)*step_y) {
            for (x = tile->coord[0][0]; x < tile->coord[0][1]; x = (x/step_x + 1)*step_x) {
                for (compno = CSpoc; compno < CEpoc; compno++) {
                    Jpeg2000Component *comp     = tile->comp + compno;
                    Jpeg2000CodingStyle *codsty = tile->codsty + compno;
                    Jpeg2000QuantStyle *qntsty  = tile->qntsty + compno;
                    int xc = x / s->cdx[compno];
                    int yc = y / s->cdy[compno];

                    for (reslevelno = RSpoc; reslevelno < FFMIN(codsty->nreslevels, REpoc); reslevelno++) {
                        unsigned prcx, prcy;
                        uint8_t reducedresno = codsty->nreslevels - 1 -reslevelno; //  ==> N_L - r
                        Jpeg2000ResLevel *rlevel = comp->reslevel + reslevelno;

                        if (yc % (1LL << (rlevel->log2_prec_height + reducedresno)) && y != tile->coord[1][0]) //FIXME this is a subset of the check
                            continue;

                        if (xc % (1LL << (rlevel->log2_prec_width + reducedresno)) && x != tile->coord[0][0]) //FIXME this is a subset of the check
                            continue;

                        // check if a precinct exists
                        prcx   = ff_jpeg2000_ceildivpow2(xc, reducedresno) >> rlevel->log2_prec_width;
                        prcy   = ff_jpeg2000_ceildivpow2(yc, reducedresno) >> rlevel->log2_prec_height;
                        prcx  -= ff_jpeg2000_ceildivpow2(comp->coord_o[0][0], reducedresno) >> rlevel->log2_prec_width;
                        prcy  -= ff_jpeg2000_ceildivpow2(comp->coord_o[1][0], reducedresno) >> rlevel->log2_prec_height;

                        precno = prcx + rlevel->num_precincts_x * prcy;

                        if (prcx >= rlevel->num_precincts_x || prcy >= rlevel->num_precincts_y) {
                            av_log(s->avctx, AV_LOG_WARNING, "prc %d %d outside limits %d %d\n",
                                   prcx, prcy, rlevel->num_precincts_x, rlevel->num_precincts_y);
                            continue;
                        }

                        for (layno = 0; layno < LYEpoc; layno++) {
                            if ((ret = jpeg2000_decode_packet(s, tile, tp_index, codsty, rlevel,
                                                              precno, layno,
                                                              qntsty->expn + (reslevelno ? 3 * (reslevelno - 1) + 1 : 0),
                                                              qntsty->nguardbits)) < 0)
                                return ret;
                        }
                    }
                }
            }
        }
        break;

    default:
        break;
    }

    return ret;
}