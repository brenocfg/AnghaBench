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
struct TYPE_3__ {unsigned int last_edge; } ;
typedef  TYPE_1__ zbar_scanner_t ;

/* Variables and functions */
 unsigned int ROUND ; 
 int ZBAR_FIXED ; 

unsigned zbar_scanner_get_edge (const zbar_scanner_t *scn,
                                unsigned offset,
                                int prec)
{
    unsigned edge = scn->last_edge - offset - (1 << ZBAR_FIXED) - ROUND;
    prec = ZBAR_FIXED - prec;
    if(prec > 0)
        return(edge >> prec);
    else if(!prec)
        return(edge);
    else
        return(edge << -prec);
}