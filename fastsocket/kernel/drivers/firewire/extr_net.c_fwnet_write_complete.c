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
struct fwnet_packet_task {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  fw_error (char*,int) ; 
 int /*<<< orphan*/  fwnet_transmit_packet_done (struct fwnet_packet_task*) ; 

__attribute__((used)) static void fwnet_write_complete(struct fw_card *card, int rcode,
				 void *payload, size_t length, void *data)
{
	struct fwnet_packet_task *ptask;

	ptask = data;

	if (rcode == RCODE_COMPLETE)
		fwnet_transmit_packet_done(ptask);
	else
		fw_error("fwnet_write_complete: failed: %x\n", rcode);
		/* ??? error recovery */
}