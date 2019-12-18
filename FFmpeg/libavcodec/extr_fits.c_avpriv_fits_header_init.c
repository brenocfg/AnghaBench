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
struct TYPE_3__ {int gcount; double bscale; scalar_t__ data_max_found; scalar_t__ data_min_found; scalar_t__ bzero; scalar_t__ image_extension; scalar_t__ rgb; scalar_t__ groups; scalar_t__ pcount; scalar_t__ blank_found; scalar_t__ naxis_index; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  FITSHeaderState ;
typedef  TYPE_1__ FITSHeader ;

/* Variables and functions */

int avpriv_fits_header_init(FITSHeader *header, FITSHeaderState state)
{
    header->state = state;
    header->naxis_index = 0;
    header->blank_found = 0;
    header->pcount = 0;
    header->gcount = 1;
    header->groups = 0;
    header->rgb = 0;
    header->image_extension = 0;
    header->bscale = 1.0;
    header->bzero = 0;
    header->data_min_found = 0;
    header->data_max_found = 0;
    return 0;
}