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
struct hpsb_packet {int header_size; int expect_response; scalar_t__ data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PREP_ASYNC_HEAD_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCODE_READQ ; 

__attribute__((used)) static void fill_async_readquad(struct hpsb_packet *packet, u64 addr)
{
	PREP_ASYNC_HEAD_ADDRESS(TCODE_READQ);
	packet->header_size = 12;
	packet->data_size = 0;
	packet->expect_response = 1;
}