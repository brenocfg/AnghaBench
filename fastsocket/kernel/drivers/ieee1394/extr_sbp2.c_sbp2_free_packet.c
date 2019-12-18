#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  hpsb_free_packet (void*) ; 
 int /*<<< orphan*/  hpsb_free_tlabel (void*) ; 

__attribute__((used)) static void sbp2_free_packet(void *packet)
{
	hpsb_free_tlabel(packet);
	hpsb_free_packet(packet);
}