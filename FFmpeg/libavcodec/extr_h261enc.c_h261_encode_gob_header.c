#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int gob_number; } ;
struct TYPE_4__ {int qscale; scalar_t__*** last_mv; scalar_t__ mb_skip_run; int /*<<< orphan*/  pb; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ H261Context ;

/* Variables and functions */
 scalar_t__ ff_h261_get_picture_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void h261_encode_gob_header(MpegEncContext *s, int mb_line)
{
    H261Context *h = (H261Context *)s;
    if (ff_h261_get_picture_format(s->width, s->height) == 0) {
        h->gob_number += 2; // QCIF
    } else {
        h->gob_number++;    // CIF
    }
    put_bits(&s->pb, 16, 1);            /* GBSC */
    put_bits(&s->pb, 4, h->gob_number); /* GN */
    put_bits(&s->pb, 5, s->qscale);     /* GQUANT */
    put_bits(&s->pb, 1, 0);             /* no GEI */
    s->mb_skip_run = 0;
    s->last_mv[0][0][0] = 0;
    s->last_mv[0][0][1] = 0;
}