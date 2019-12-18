#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int** coord; int** coord_o; } ;
struct TYPE_9__ {int numXtiles; int tile_width; int numYtiles; int tile_height; int ncomponents; int* chroma_shift; int /*<<< orphan*/  avctx; int /*<<< orphan*/ * cbps; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* tile; int /*<<< orphan*/  qntsty; int /*<<< orphan*/  codsty; } ;
struct TYPE_8__ {TYPE_3__* comp; } ;
typedef  TYPE_1__ Jpeg2000Tile ;
typedef  int /*<<< orphan*/  Jpeg2000QuantStyle ;
typedef  TYPE_2__ Jpeg2000EncoderContext ;
typedef  TYPE_3__ Jpeg2000Component ;
typedef  int /*<<< orphan*/  Jpeg2000CodingStyle ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFMIN (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* av_malloc_array (int,int) ; 
 TYPE_3__* av_mallocz_array (int,int) ; 
 void* ff_jpeg2000_ceildiv (int /*<<< orphan*/ ,int) ; 
 int ff_jpeg2000_ceildivpow2 (int,int) ; 
 int ff_jpeg2000_init_component (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_tiles(Jpeg2000EncoderContext *s)
{
    int tileno, tilex, tiley, compno;
    Jpeg2000CodingStyle *codsty = &s->codsty;
    Jpeg2000QuantStyle  *qntsty = &s->qntsty;

    s->numXtiles = ff_jpeg2000_ceildiv(s->width, s->tile_width);
    s->numYtiles = ff_jpeg2000_ceildiv(s->height, s->tile_height);

    s->tile = av_malloc_array(s->numXtiles, s->numYtiles * sizeof(Jpeg2000Tile));
    if (!s->tile)
        return AVERROR(ENOMEM);
    for (tileno = 0, tiley = 0; tiley < s->numYtiles; tiley++)
        for (tilex = 0; tilex < s->numXtiles; tilex++, tileno++){
            Jpeg2000Tile *tile = s->tile + tileno;

            tile->comp = av_mallocz_array(s->ncomponents, sizeof(Jpeg2000Component));
            if (!tile->comp)
                return AVERROR(ENOMEM);
            for (compno = 0; compno < s->ncomponents; compno++){
                Jpeg2000Component *comp = tile->comp + compno;
                int ret, i, j;

                comp->coord[0][0] = comp->coord_o[0][0] = tilex * s->tile_width;
                comp->coord[0][1] = comp->coord_o[0][1] = FFMIN((tilex+1)*s->tile_width, s->width);
                comp->coord[1][0] = comp->coord_o[1][0] = tiley * s->tile_height;
                comp->coord[1][1] = comp->coord_o[1][1] = FFMIN((tiley+1)*s->tile_height, s->height);
                if (compno > 0)
                    for (i = 0; i < 2; i++)
                        for (j = 0; j < 2; j++)
                            comp->coord[i][j] = comp->coord_o[i][j] = ff_jpeg2000_ceildivpow2(comp->coord[i][j], s->chroma_shift[i]);

                if ((ret = ff_jpeg2000_init_component(comp,
                                                codsty,
                                                qntsty,
                                                s->cbps[compno],
                                                compno?1<<s->chroma_shift[0]:1,
                                                compno?1<<s->chroma_shift[1]:1,
                                                s->avctx
                                               )) < 0)
                    return ret;
            }
        }
    return 0;
}