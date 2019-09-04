#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_36__ {scalar_t__** coord; TYPE_4__* prec; } ;
struct TYPE_35__ {int** coord; } ;
struct TYPE_34__ {int log2_cblk_width; int nreslevels2decode; scalar_t__ transform; } ;
struct TYPE_33__ {scalar_t__ i_data; scalar_t__ f_data; int /*<<< orphan*/  dwt; TYPE_3__* reslevel; } ;
struct TYPE_32__ {int ncomponents; } ;
struct TYPE_31__ {int nb_codeblocks_width; int nb_codeblocks_height; TYPE_8__* cblk; } ;
struct TYPE_30__ {int nbands; int num_precincts_x; int num_precincts_y; TYPE_9__* band; } ;
struct TYPE_29__ {int stride; } ;
struct TYPE_28__ {TYPE_7__* codsty; TYPE_6__* comp; } ;
typedef  TYPE_1__ Jpeg2000Tile ;
typedef  TYPE_2__ Jpeg2000T1Context ;
typedef  TYPE_3__ Jpeg2000ResLevel ;
typedef  TYPE_4__ Jpeg2000Prec ;
typedef  TYPE_5__ Jpeg2000DecoderContext ;
typedef  TYPE_6__ Jpeg2000Component ;
typedef  TYPE_7__ Jpeg2000CodingStyle ;
typedef  TYPE_8__ Jpeg2000Cblk ;
typedef  TYPE_9__ Jpeg2000Band ;

/* Variables and functions */
 scalar_t__ FF_DWT97 ; 
 scalar_t__ FF_DWT97_INT ; 
 int decode_cblk (TYPE_5__*,TYPE_7__*,TYPE_2__*,TYPE_8__*,int,int,int) ; 
 int /*<<< orphan*/  dequantization_float (int,int,TYPE_8__*,TYPE_6__*,TYPE_2__*,TYPE_9__*) ; 
 int /*<<< orphan*/  dequantization_int (int,int,TYPE_8__*,TYPE_6__*,TYPE_2__*,TYPE_9__*) ; 
 int /*<<< orphan*/  dequantization_int_97 (int,int,TYPE_8__*,TYPE_6__*,TYPE_2__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ff_dwt_decode (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline void tile_codeblocks(Jpeg2000DecoderContext *s, Jpeg2000Tile *tile)
{
    Jpeg2000T1Context t1;

    int compno, reslevelno, bandno;

    /* Loop on tile components */
    for (compno = 0; compno < s->ncomponents; compno++) {
        Jpeg2000Component *comp     = tile->comp + compno;
        Jpeg2000CodingStyle *codsty = tile->codsty + compno;
        int coded = 0;

        t1.stride = (1<<codsty->log2_cblk_width) + 2;

        /* Loop on resolution levels */
        for (reslevelno = 0; reslevelno < codsty->nreslevels2decode; reslevelno++) {
            Jpeg2000ResLevel *rlevel = comp->reslevel + reslevelno;
            /* Loop on bands */
            for (bandno = 0; bandno < rlevel->nbands; bandno++) {
                int nb_precincts, precno;
                Jpeg2000Band *band = rlevel->band + bandno;
                int cblkno = 0, bandpos;

                bandpos = bandno + (reslevelno > 0);

                if (band->coord[0][0] == band->coord[0][1] ||
                    band->coord[1][0] == band->coord[1][1])
                    continue;

                nb_precincts = rlevel->num_precincts_x * rlevel->num_precincts_y;
                /* Loop on precincts */
                for (precno = 0; precno < nb_precincts; precno++) {
                    Jpeg2000Prec *prec = band->prec + precno;

                    /* Loop on codeblocks */
                    for (cblkno = 0;
                         cblkno < prec->nb_codeblocks_width * prec->nb_codeblocks_height;
                         cblkno++) {
                        int x, y;
                        Jpeg2000Cblk *cblk = prec->cblk + cblkno;
                        int ret = decode_cblk(s, codsty, &t1, cblk,
                                    cblk->coord[0][1] - cblk->coord[0][0],
                                    cblk->coord[1][1] - cblk->coord[1][0],
                                    bandpos);
                        if (ret)
                            coded = 1;
                        else
                            continue;
                        x = cblk->coord[0][0] - band->coord[0][0];
                        y = cblk->coord[1][0] - band->coord[1][0];

                        if (codsty->transform == FF_DWT97)
                            dequantization_float(x, y, cblk, comp, &t1, band);
                        else if (codsty->transform == FF_DWT97_INT)
                            dequantization_int_97(x, y, cblk, comp, &t1, band);
                        else
                            dequantization_int(x, y, cblk, comp, &t1, band);
                   } /* end cblk */
                } /*end prec */
            } /* end band */
        } /* end reslevel */

        /* inverse DWT */
        if (coded)
            ff_dwt_decode(&comp->dwt, codsty->transform == FF_DWT97 ? (void*)comp->f_data : (void*)comp->i_data);

    } /*end comp */
}