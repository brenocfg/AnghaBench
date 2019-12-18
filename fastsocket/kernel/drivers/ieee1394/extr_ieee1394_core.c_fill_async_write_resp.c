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
struct hpsb_packet {int header_size; scalar_t__ data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PREP_ASYNC_HEAD_RCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCODE_WRITE_RESPONSE ; 

__attribute__((used)) static void fill_async_write_resp(struct hpsb_packet *packet, int rcode)
{
	PREP_ASYNC_HEAD_RCODE(TCODE_WRITE_RESPONSE);
	packet->header_size = 12;
	packet->data_size = 0;
}