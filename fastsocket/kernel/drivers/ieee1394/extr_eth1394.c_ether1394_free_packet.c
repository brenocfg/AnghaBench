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
struct hpsb_packet {scalar_t__ tcode; } ;

/* Variables and functions */
 scalar_t__ TCODE_STREAM_DATA ; 
 int /*<<< orphan*/  hpsb_free_packet (struct hpsb_packet*) ; 
 int /*<<< orphan*/  hpsb_free_tlabel (struct hpsb_packet*) ; 

__attribute__((used)) static void ether1394_free_packet(struct hpsb_packet *packet)
{
	if (packet->tcode != TCODE_STREAM_DATA)
		hpsb_free_tlabel(packet);
	hpsb_free_packet(packet);
}