#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int format; TYPE_1__* dst; } ;
struct TYPE_6__ {int hi_pixel_mask; int lo_pixel_mask; int q_hi_pixel_mask; int q_lo_pixel_mask; int bpp; int is_be; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ Super2xSaIContext ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
#define  AV_PIX_FMT_BGR24 137 
#define  AV_PIX_FMT_BGR555BE 136 
#define  AV_PIX_FMT_BGR555LE 135 
#define  AV_PIX_FMT_BGR565BE 134 
#define  AV_PIX_FMT_BGR565LE 133 
#define  AV_PIX_FMT_RGB24 132 
#define  AV_PIX_FMT_RGB555BE 131 
#define  AV_PIX_FMT_RGB555LE 130 
#define  AV_PIX_FMT_RGB565BE 129 
#define  AV_PIX_FMT_RGB565LE 128 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    Super2xSaIContext *s = inlink->dst->priv;

    s->hi_pixel_mask   = 0xFEFEFEFE;
    s->lo_pixel_mask   = 0x01010101;
    s->q_hi_pixel_mask = 0xFCFCFCFC;
    s->q_lo_pixel_mask = 0x03030303;
    s->bpp  = 4;

    switch (inlink->format) {
    case AV_PIX_FMT_RGB24:
    case AV_PIX_FMT_BGR24:
        s->bpp = 3;
        break;

    case AV_PIX_FMT_RGB565BE:
    case AV_PIX_FMT_BGR565BE:
        s->is_be = 1;
    case AV_PIX_FMT_RGB565LE:
    case AV_PIX_FMT_BGR565LE:
        s->hi_pixel_mask   = 0xF7DEF7DE;
        s->lo_pixel_mask   = 0x08210821;
        s->q_hi_pixel_mask = 0xE79CE79C;
        s->q_lo_pixel_mask = 0x18631863;
        s->bpp = 2;
        break;

    case AV_PIX_FMT_BGR555BE:
    case AV_PIX_FMT_RGB555BE:
        s->is_be = 1;
    case AV_PIX_FMT_BGR555LE:
    case AV_PIX_FMT_RGB555LE:
        s->hi_pixel_mask   = 0x7BDE7BDE;
        s->lo_pixel_mask   = 0x04210421;
        s->q_hi_pixel_mask = 0x739C739C;
        s->q_lo_pixel_mask = 0x0C630C63;
        s->bpp = 2;
        break;
    }

    return 0;
}