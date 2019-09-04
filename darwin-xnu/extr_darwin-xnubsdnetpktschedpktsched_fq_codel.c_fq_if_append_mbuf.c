#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mbuf_t ;
struct TYPE_2__ {struct TYPE_2__* m_nextpkt; } ;

/* Variables and functions */

__attribute__((used)) static void
fq_if_append_mbuf(void *pkt, void *next_pkt)
{
	((mbuf_t)pkt)->m_nextpkt = (mbuf_t)next_pkt;
}