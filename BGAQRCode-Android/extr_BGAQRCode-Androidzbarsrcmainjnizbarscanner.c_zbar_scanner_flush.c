#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_4__ {scalar_t__ y1_sign; unsigned int x; unsigned int cur_edge; scalar_t__ width; scalar_t__ decoder; } ;
typedef  TYPE_1__ zbar_scanner_t ;

/* Variables and functions */
 unsigned int ROUND ; 
 unsigned int ZBAR_FIXED ; 
 int /*<<< orphan*/  ZBAR_NONE ; 
 int /*<<< orphan*/  ZBAR_PARTIAL ; 
 int /*<<< orphan*/  dbprintf (int,char*) ; 
 int /*<<< orphan*/  process_edge (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  zbar_decode_width (scalar_t__,int /*<<< orphan*/ ) ; 

inline zbar_symbol_type_t zbar_scanner_flush (zbar_scanner_t *scn)
{
    unsigned x;
    if(!scn->y1_sign)
        return(ZBAR_NONE);

    x = (scn->x << ZBAR_FIXED) + ROUND;

    if(scn->cur_edge != x || scn->y1_sign > 0) {
        zbar_symbol_type_t edge = process_edge(scn, -scn->y1_sign);
        dbprintf(1, "flush0:");
        scn->cur_edge = x;
        scn->y1_sign = -scn->y1_sign;
        return(edge);
    }

    scn->y1_sign = scn->width = 0;
    if(scn->decoder)
        return(zbar_decode_width(scn->decoder, 0));
    return(ZBAR_PARTIAL);
}