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
typedef  scalar_t__ int32_t ;
typedef  TYPE_1__* bondport_ref ;
typedef  scalar_t__ __darwin_time_t ;
struct TYPE_3__ {scalar_t__ po_last_transmit_secs; scalar_t__ po_n_transmit; } ;

/* Variables and functions */
 scalar_t__ LACP_PACKET_RATE ; 

__attribute__((used)) static int
bondport_can_transmit(bondport_ref p, int32_t current_secs,
		      __darwin_time_t * next_secs)
{
    if (p->po_last_transmit_secs != current_secs) {
	p->po_last_transmit_secs = current_secs;
	p->po_n_transmit = 0;
    }
    if (p->po_n_transmit < LACP_PACKET_RATE) {
	p->po_n_transmit++;
	return (1);
    }
    if (next_secs != NULL) {
	*next_secs = current_secs + 1;
    }
    return (0);
}