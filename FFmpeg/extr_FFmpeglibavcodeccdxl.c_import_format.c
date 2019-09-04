#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int format; TYPE_1__* avctx; } ;
struct TYPE_7__ {int height; } ;
typedef  TYPE_2__ CDXLVideoContext ;

/* Variables and functions */
#define  BIT_LINE 130 
#define  BIT_PLANAR 129 
#define  CHUNKY 128 
 int /*<<< orphan*/  bitline2chunky (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitplanar2chunky (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chunky2chunky (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void import_format(CDXLVideoContext *c, int linesize, uint8_t *out)
{
    memset(out, 0, linesize * c->avctx->height);

    switch (c->format) {
    case BIT_PLANAR:
        bitplanar2chunky(c, linesize, out);
        break;
    case BIT_LINE:
        bitline2chunky(c, linesize, out);
        break;
    case CHUNKY:
        chunky2chunky(c, linesize, out);
        break;
    }
}