#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_3__ {int last_edge; int cur_edge; int width; scalar_t__ decoder; int /*<<< orphan*/  y1_sign; } ;
typedef  TYPE_1__ zbar_scanner_t ;

/* Variables and functions */
 int ROUND ; 
 int ZBAR_FIXED ; 
 int /*<<< orphan*/  ZBAR_PARTIAL ; 
 int /*<<< orphan*/  dbprintf (int,char*,int /*<<< orphan*/ ,int,int,int,char*) ; 
 int /*<<< orphan*/  zbar_decode_width (scalar_t__,int) ; 

__attribute__((used)) static inline zbar_symbol_type_t process_edge (zbar_scanner_t *scn,
                                               int y1)
{
    if(!scn->y1_sign)
        scn->last_edge = scn->cur_edge = (1 << ZBAR_FIXED) + ROUND;
    else if(!scn->last_edge)
        scn->last_edge = scn->cur_edge;

    scn->width = scn->cur_edge - scn->last_edge;
    dbprintf(1, " sgn=%d cur=%d.%d w=%d (%s)\n",
             scn->y1_sign, scn->cur_edge >> ZBAR_FIXED,
             scn->cur_edge & ((1 << ZBAR_FIXED) - 1), scn->width,
             ((y1 > 0) ? "SPACE" : "BAR"));
    scn->last_edge = scn->cur_edge;

#if DEBUG_SVG > 1
    svg_path_moveto(SVG_ABS, scn->last_edge - (1 << ZBAR_FIXED) - ROUND, 0);
#endif

    /* pass to decoder */
    if(scn->decoder)
        return(zbar_decode_width(scn->decoder, scn->width));
    return(ZBAR_PARTIAL);
}