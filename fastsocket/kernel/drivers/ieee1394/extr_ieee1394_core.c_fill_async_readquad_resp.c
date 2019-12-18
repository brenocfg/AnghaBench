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
struct hpsb_packet {int header_size; scalar_t__ data_size; int /*<<< orphan*/ * header; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 int /*<<< orphan*/  PREP_ASYNC_HEAD_RCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCODE_READQ_RESPONSE ; 

__attribute__((used)) static void fill_async_readquad_resp(struct hpsb_packet *packet, int rcode,
			      quadlet_t data)
{
	PREP_ASYNC_HEAD_RCODE(TCODE_READQ_RESPONSE);
	packet->header[3] = data;
	packet->header_size = 16;
	packet->data_size = 0;
}