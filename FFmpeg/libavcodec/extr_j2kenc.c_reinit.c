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
struct TYPE_5__ {int numXtiles; int numYtiles; int ncomponents; int /*<<< orphan*/  codsty; TYPE_1__* tile; } ;
struct TYPE_4__ {scalar_t__ comp; } ;
typedef  TYPE_1__ Jpeg2000Tile ;
typedef  TYPE_2__ Jpeg2000EncoderContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_jpeg2000_reinit (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reinit(Jpeg2000EncoderContext *s)
{
    int tileno, compno;
    for (tileno = 0; tileno < s->numXtiles * s->numYtiles; tileno++){
        Jpeg2000Tile *tile = s->tile + tileno;
        for (compno = 0; compno < s->ncomponents; compno++)
            ff_jpeg2000_reinit(tile->comp + compno, &s->codsty);
    }
}