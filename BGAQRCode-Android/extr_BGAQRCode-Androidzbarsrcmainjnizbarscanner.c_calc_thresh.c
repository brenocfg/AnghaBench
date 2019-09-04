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
struct TYPE_3__ {unsigned int y1_thresh; unsigned int y1_min_thresh; unsigned long width; int x; int last_edge; } ;
typedef  TYPE_1__ zbar_scanner_t ;

/* Variables and functions */
 int ZBAR_FIXED ; 
 unsigned long ZBAR_SCANNER_THRESH_FADE ; 
 int /*<<< orphan*/  dbprintf (int,char*,unsigned int,...) ; 

__attribute__((used)) static inline unsigned calc_thresh (zbar_scanner_t *scn)
{
    /* threshold 1st to improve noise rejection */
    unsigned dx, thresh = scn->y1_thresh;
    unsigned long t;
    if((thresh <= scn->y1_min_thresh) || !scn->width) {
        dbprintf(1, " tmin=%d", scn->y1_min_thresh);
        return(scn->y1_min_thresh);
    }
    /* slowly return threshold to min */
    dx = (scn->x << ZBAR_FIXED) - scn->last_edge;
    t = thresh * dx;
    t /= scn->width;
    t /= ZBAR_SCANNER_THRESH_FADE;
    dbprintf(1, " thr=%d t=%ld x=%d last=%d.%d (%d)",
             thresh, t, scn->x, scn->last_edge >> ZBAR_FIXED,
             scn->last_edge & ((1 << ZBAR_FIXED) - 1), dx);
    if(thresh > t) {
        thresh -= t;
        if(thresh > scn->y1_min_thresh)
            return(thresh);
    }
    scn->y1_thresh = scn->y1_min_thresh;
    return(scn->y1_min_thresh);
}