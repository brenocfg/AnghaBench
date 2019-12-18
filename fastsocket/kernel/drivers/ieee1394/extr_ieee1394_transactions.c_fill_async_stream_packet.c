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
struct hpsb_packet {int* header; int header_size; int data_size; int /*<<< orphan*/  tcode; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_ISO_DATA ; 
 int TCODE_STREAM_DATA ; 
 int /*<<< orphan*/  hpsb_async ; 

__attribute__((used)) static void fill_async_stream_packet(struct hpsb_packet *packet, int length,
				     int channel, int tag, int sync)
{
	packet->header[0] = (length << 16) | (tag << 14) | (channel << 8)
	    | (TCODE_STREAM_DATA << 4) | sync;

	packet->header_size = 4;
	packet->data_size = length;
	packet->type = hpsb_async;
	packet->tcode = TCODE_ISO_DATA;
}