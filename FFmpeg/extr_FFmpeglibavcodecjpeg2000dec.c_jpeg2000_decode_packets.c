#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int bit_index; int /*<<< orphan*/  g; int /*<<< orphan*/  ncomponents; } ;
struct TYPE_13__ {int REpoc; int /*<<< orphan*/  Ppoc; int /*<<< orphan*/  CEpoc; int /*<<< orphan*/  LYEpoc; int /*<<< orphan*/  CSpoc; int /*<<< orphan*/  RSpoc; } ;
struct TYPE_10__ {int nb_poc; TYPE_4__* poc; } ;
struct TYPE_12__ {TYPE_2__* codsty; TYPE_1__ poc; } ;
struct TYPE_11__ {int /*<<< orphan*/  prog_order; int /*<<< orphan*/  nlayers; } ;
typedef  TYPE_3__ Jpeg2000Tile ;
typedef  TYPE_4__ Jpeg2000POCEntry ;
typedef  TYPE_5__ Jpeg2000DecoderContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int jpeg2000_decode_packets_po_iteration (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int jpeg2000_decode_packets(Jpeg2000DecoderContext *s, Jpeg2000Tile *tile)
{
    int ret = AVERROR_BUG;
    int i;
    int tp_index = 0;

    s->bit_index = 8;
    if (tile->poc.nb_poc) {
        for (i=0; i<tile->poc.nb_poc; i++) {
            Jpeg2000POCEntry *e = &tile->poc.poc[i];
            ret = jpeg2000_decode_packets_po_iteration(s, tile,
                e->RSpoc, e->CSpoc,
                FFMIN(e->LYEpoc, tile->codsty[0].nlayers),
                e->REpoc,
                FFMIN(e->CEpoc, s->ncomponents),
                e->Ppoc, &tp_index
                );
            if (ret < 0)
                return ret;
        }
    } else {
        ret = jpeg2000_decode_packets_po_iteration(s, tile,
            0, 0,
            tile->codsty[0].nlayers,
            33,
            s->ncomponents,
            tile->codsty[0].prog_order,
            &tp_index
        );
    }
    /* EOC marker reached */
    bytestream2_skip(&s->g, 2);

    return ret;
}