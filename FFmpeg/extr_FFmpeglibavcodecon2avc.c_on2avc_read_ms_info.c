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
struct TYPE_3__ {int num_windows; int num_bands; void** ms_info; int /*<<< orphan*/ * grouping; void* ms_present; } ;
typedef  TYPE_1__ On2AVCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 

__attribute__((used)) static void on2avc_read_ms_info(On2AVCContext *c, GetBitContext *gb)
{
    int w, b, band_off = 0;

    c->ms_present = get_bits1(gb);
    if (!c->ms_present)
        return;
    for (w = 0; w < c->num_windows; w++) {
        if (!c->grouping[w]) {
            memcpy(c->ms_info + band_off,
                   c->ms_info + band_off - c->num_bands,
                   c->num_bands * sizeof(*c->ms_info));
            band_off += c->num_bands;
            continue;
        }
        for (b = 0; b < c->num_bands; b++)
            c->ms_info[band_off++] = get_bits1(gb);
    }
}