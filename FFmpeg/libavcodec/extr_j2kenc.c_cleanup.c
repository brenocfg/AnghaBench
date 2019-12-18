#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* comp; } ;
struct TYPE_6__ {int numXtiles; int numYtiles; int ncomponents; TYPE_2__* tile; int /*<<< orphan*/  codsty; } ;
typedef  TYPE_1__ Jpeg2000EncoderContext ;
typedef  TYPE_2__ Jpeg2000Component ;
typedef  int /*<<< orphan*/  Jpeg2000CodingStyle ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  ff_jpeg2000_cleanup (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup(Jpeg2000EncoderContext *s)
{
    int tileno, compno;
    Jpeg2000CodingStyle *codsty = &s->codsty;

    for (tileno = 0; tileno < s->numXtiles * s->numYtiles; tileno++){
        for (compno = 0; compno < s->ncomponents; compno++){
            Jpeg2000Component *comp = s->tile[tileno].comp + compno;
            ff_jpeg2000_cleanup(comp, codsty);
        }
        av_freep(&s->tile[tileno].comp);
    }
    av_freep(&s->tile);
}