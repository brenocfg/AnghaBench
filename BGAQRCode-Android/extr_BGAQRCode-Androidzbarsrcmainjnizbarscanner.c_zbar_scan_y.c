#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_5__ {int x; int* y0; int y1_sign; int y1_thresh; int y1_min_thresh; int cur_edge; } ;
typedef  TYPE_1__ zbar_scanner_t ;

/* Variables and functions */
 int EWMA_WEIGHT ; 
 int ROUND ; 
 int THRESH_INIT ; 
 int ZBAR_FIXED ; 
 int /*<<< orphan*/  ZBAR_NONE ; 
 int abs (int) ; 
 int calc_thresh (TYPE_1__*) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int /*<<< orphan*/  process_edge (TYPE_1__*,int) ; 

zbar_symbol_type_t zbar_scan_y (zbar_scanner_t *scn,
                                int y)
{
    /* FIXME calc and clip to max y range... */
    /* retrieve short value history */
    register int x = scn->x;
    register int y0_1 = scn->y0[(x - 1) & 3];
    register int y0_0 = y0_1;
    register int y0_2, y0_3, y1_1, y2_1, y2_2;
    zbar_symbol_type_t edge;
    if(x) {
        /* update weighted moving average */
        y0_0 += ((int)((y - y0_1) * EWMA_WEIGHT)) >> ZBAR_FIXED;
        scn->y0[x & 3] = y0_0;
    }
    else
        y0_0 = y0_1 = scn->y0[0] = scn->y0[1] = scn->y0[2] = scn->y0[3] = y;
    y0_2 = scn->y0[(x - 2) & 3];
    y0_3 = scn->y0[(x - 3) & 3];
    /* 1st differential @ x-1 */
    y1_1 = y0_1 - y0_2;
    {
        register int y1_2 = y0_2 - y0_3;
        if((abs(y1_1) < abs(y1_2)) &&
           ((y1_1 >= 0) == (y1_2 >= 0)))
            y1_1 = y1_2;
    }

    /* 2nd differentials @ x-1 & x-2 */
    y2_1 = y0_0 - (y0_1 * 2) + y0_2;
    y2_2 = y0_1 - (y0_2 * 2) + y0_3;

    dbprintf(1, "scan: x=%d y=%d y0=%d y1=%d y2=%d",
             x, y, y0_1, y1_1, y2_1);

    edge = ZBAR_NONE;
    /* 2nd zero-crossing is 1st local min/max - could be edge */
    if((!y2_1 ||
        ((y2_1 > 0) ? y2_2 < 0 : y2_2 > 0)) &&
       (calc_thresh(scn) <= abs(y1_1)))
    {
        /* check for 1st sign change */
        char y1_rev = (scn->y1_sign > 0) ? y1_1 < 0 : y1_1 > 0;
        if(y1_rev)
            /* intensity change reversal - finalize previous edge */
            edge = process_edge(scn, y1_1);

        if(y1_rev || (abs(scn->y1_sign) < abs(y1_1))) {
            int d;
            scn->y1_sign = y1_1;

            /* adaptive thresholding */
            /* start at multiple of new min/max */
            scn->y1_thresh = (abs(y1_1) * THRESH_INIT + ROUND) >> ZBAR_FIXED;
            dbprintf(1, "\tthr=%d", scn->y1_thresh);
            if(scn->y1_thresh < scn->y1_min_thresh)
                scn->y1_thresh = scn->y1_min_thresh;

            /* update current edge */
            d = y2_1 - y2_2;
            scn->cur_edge = 1 << ZBAR_FIXED;
            if(!d)
                scn->cur_edge >>= 1;
            else if(y2_1)
                /* interpolate zero crossing */
                scn->cur_edge -= ((y2_1 << ZBAR_FIXED) + 1) / d;
            scn->cur_edge += x << ZBAR_FIXED;
            dbprintf(1, "\n");
        }
    }
    else
        dbprintf(1, "\n");
    /* FIXME add fall-thru pass to decoder after heuristic "idle" period
       (eg, 6-8 * last width) */
    scn->x = x + 1;
    return(edge);
}