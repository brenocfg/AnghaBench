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
struct pktcdvd_device {int dummy; } ;
struct packet_command {int* cmd; int quiet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_NONE ; 
 int GPCMD_FLUSH_CACHE ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pkt_generic_packet (struct pktcdvd_device*,struct packet_command*) ; 

__attribute__((used)) static int pkt_flush_cache(struct pktcdvd_device *pd)
{
	struct packet_command cgc;

	init_cdrom_command(&cgc, NULL, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_FLUSH_CACHE;
	cgc.quiet = 1;

	/*
	 * the IMMED bit -- we default to not setting it, although that
	 * would allow a much faster close, this is safer
	 */
#if 0
	cgc.cmd[1] = 1 << 1;
#endif
	return pkt_generic_packet(pd, &cgc);
}