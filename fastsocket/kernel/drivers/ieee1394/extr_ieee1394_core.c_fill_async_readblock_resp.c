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
struct hpsb_packet {int* header; int header_size; int data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PREP_ASYNC_HEAD_RCODE (int /*<<< orphan*/ ) ; 
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  TCODE_READB_RESPONSE ; 

__attribute__((used)) static void fill_async_readblock_resp(struct hpsb_packet *packet, int rcode,
			       int length)
{
	if (rcode != RCODE_COMPLETE)
		length = 0;

	PREP_ASYNC_HEAD_RCODE(TCODE_READB_RESPONSE);
	packet->header[3] = length << 16;
	packet->header_size = 16;
	packet->data_size = length + (length % 4 ? 4 - (length % 4) : 0);
}