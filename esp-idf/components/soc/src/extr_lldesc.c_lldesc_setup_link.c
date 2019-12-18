#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {TYPE_2__* stqe_next; } ;
struct TYPE_5__ {int size; int length; int eof; int owner; TYPE_1__ qe; scalar_t__ sosf; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_2__ lldesc_t ;

/* Variables and functions */
 int LLDESC_MAX_NUM_PER_DESC ; 

void lldesc_setup_link(lldesc_t *dmadesc, const void *data, int len, bool isrx)
{
    int n = 0;
    while (len) {
        int dmachunklen = len;
        if (dmachunklen > LLDESC_MAX_NUM_PER_DESC) {
            dmachunklen = LLDESC_MAX_NUM_PER_DESC;
        }
        if (isrx) {
            //Receive needs DMA length rounded to next 32-bit boundary
            dmadesc[n].size = (dmachunklen + 3) & (~3);
            dmadesc[n].length = (dmachunklen + 3) & (~3);
        } else {
            dmadesc[n].size = dmachunklen;
            dmadesc[n].length = dmachunklen;
        }
        dmadesc[n].buf = (uint8_t *)data;
        dmadesc[n].eof = 0;
        dmadesc[n].sosf = 0;
        dmadesc[n].owner = 1;
        dmadesc[n].qe.stqe_next = &dmadesc[n + 1];
        len -= dmachunklen;
        data += dmachunklen;
        n++;
    }
    dmadesc[n - 1].eof = 1; //Mark last DMA desc as end of stream.
    dmadesc[n - 1].qe.stqe_next = NULL;
}