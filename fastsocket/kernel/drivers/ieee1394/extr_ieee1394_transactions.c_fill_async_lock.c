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
typedef  int /*<<< orphan*/  u64 ;
struct hpsb_packet {int* header; int header_size; int data_size; int expect_response; } ;

/* Variables and functions */
 int /*<<< orphan*/  PREP_ASYNC_HEAD_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCODE_LOCK_REQUEST ; 

__attribute__((used)) static void fill_async_lock(struct hpsb_packet *packet, u64 addr, int extcode,
			    int length)
{
	PREP_ASYNC_HEAD_ADDRESS(TCODE_LOCK_REQUEST);
	packet->header[3] = (length << 16) | extcode;
	packet->header_size = 16;
	packet->data_size = length;
	packet->expect_response = 1;
}