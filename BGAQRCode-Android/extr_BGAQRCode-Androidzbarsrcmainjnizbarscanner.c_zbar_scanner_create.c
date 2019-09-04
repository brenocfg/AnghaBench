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
struct TYPE_5__ {int /*<<< orphan*/  y1_min_thresh; int /*<<< orphan*/ * decoder; } ;
typedef  TYPE_1__ zbar_scanner_t ;
typedef  int /*<<< orphan*/  zbar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_SCANNER_THRESH_MIN ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  zbar_scanner_reset (TYPE_1__*) ; 

zbar_scanner_t *zbar_scanner_create (zbar_decoder_t *dcode)
{
    zbar_scanner_t *scn = malloc(sizeof(zbar_scanner_t));
    scn->decoder = dcode;
    scn->y1_min_thresh = ZBAR_SCANNER_THRESH_MIN;
    zbar_scanner_reset(scn);
    return(scn);
}