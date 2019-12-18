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
struct TYPE_2__ {int /*<<< orphan*/ * listen_pcbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memb_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uip_listen_tcp_pcbs ; 
 int /*<<< orphan*/ * uip_tcp_active_pcbs ; 
 TYPE_1__ uip_tcp_listen_pcbs ; 
 int /*<<< orphan*/  uip_tcp_pcbs ; 
 int /*<<< orphan*/  uip_tcp_segs ; 
 scalar_t__ uip_tcp_ticks ; 
 scalar_t__ uip_tcp_timer ; 
 int /*<<< orphan*/ * uip_tcp_tw_pcbs ; 

void uip_tcp_init()
{
	memb_init(&uip_tcp_pcbs);
	memb_init(&uip_listen_tcp_pcbs);
	memb_init(&uip_tcp_segs);

	uip_tcp_listen_pcbs.listen_pcbs = NULL;
	uip_tcp_active_pcbs = NULL;
	uip_tcp_tw_pcbs = NULL;

	uip_tcp_ticks = 0;
	uip_tcp_timer = 0;
}