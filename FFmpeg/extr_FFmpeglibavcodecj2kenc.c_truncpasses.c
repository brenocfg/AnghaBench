#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_19__ {scalar_t__ i_stepsize; TYPE_3__* prec; } ;
struct TYPE_18__ {int /*<<< orphan*/  ninclpasses; } ;
struct TYPE_17__ {int nreslevels; scalar_t__ transform; } ;
struct TYPE_16__ {TYPE_2__* reslevel; } ;
struct TYPE_15__ {int ncomponents; int /*<<< orphan*/  lambda; TYPE_6__ codsty; } ;
struct TYPE_14__ {int nb_codeblocks_height; int nb_codeblocks_width; TYPE_7__* cblk; } ;
struct TYPE_13__ {int num_precincts_x; int num_precincts_y; int nbands; TYPE_8__* band; } ;
struct TYPE_12__ {TYPE_5__* comp; } ;
typedef  TYPE_1__ Jpeg2000Tile ;
typedef  TYPE_2__ Jpeg2000ResLevel ;
typedef  TYPE_3__ Jpeg2000Prec ;
typedef  TYPE_4__ Jpeg2000EncoderContext ;
typedef  TYPE_5__ Jpeg2000Component ;
typedef  TYPE_6__ Jpeg2000CodingStyle ;
typedef  TYPE_7__ Jpeg2000Cblk ;
typedef  TYPE_8__ Jpeg2000Band ;

/* Variables and functions */
 scalar_t__ FF_DWT53 ; 
 scalar_t__*** dwt_norms ; 
 int /*<<< orphan*/  getcut (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void truncpasses(Jpeg2000EncoderContext *s, Jpeg2000Tile *tile)
{
    int precno, compno, reslevelno, bandno, cblkno, lev;
    Jpeg2000CodingStyle *codsty = &s->codsty;

    for (compno = 0; compno < s->ncomponents; compno++){
        Jpeg2000Component *comp = tile->comp + compno;

        for (reslevelno = 0, lev = codsty->nreslevels-1; reslevelno < codsty->nreslevels; reslevelno++, lev--){
            Jpeg2000ResLevel *reslevel = comp->reslevel + reslevelno;

            for (precno = 0; precno < reslevel->num_precincts_x * reslevel->num_precincts_y; precno++){
                for (bandno = 0; bandno < reslevel->nbands ; bandno++){
                    int bandpos = bandno + (reslevelno > 0);
                    Jpeg2000Band *band = reslevel->band + bandno;
                    Jpeg2000Prec *prec = band->prec + precno;

                    for (cblkno = 0; cblkno < prec->nb_codeblocks_height * prec->nb_codeblocks_width; cblkno++){
                        Jpeg2000Cblk *cblk = prec->cblk + cblkno;

                        cblk->ninclpasses = getcut(cblk, s->lambda,
                                (int64_t)dwt_norms[codsty->transform == FF_DWT53][bandpos][lev] * (int64_t)band->i_stepsize >> 15);
                    }
                }
            }
        }
    }
}