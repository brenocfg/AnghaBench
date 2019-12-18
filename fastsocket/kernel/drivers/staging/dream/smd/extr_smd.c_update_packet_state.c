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
struct smd_channel {unsigned int current_packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SMD_HEADER_SIZE ; 
 int ch_read (struct smd_channel*,unsigned int*,int) ; 
 int smd_stream_read_avail (struct smd_channel*) ; 

__attribute__((used)) static void update_packet_state(struct smd_channel *ch)
{
	unsigned hdr[5];
	int r;

	/* can't do anything if we're in the middle of a packet */
	if (ch->current_packet != 0)
		return;

	/* don't bother unless we can get the full header */
	if (smd_stream_read_avail(ch) < SMD_HEADER_SIZE)
		return;

	r = ch_read(ch, hdr, SMD_HEADER_SIZE);
	BUG_ON(r != SMD_HEADER_SIZE);

	ch->current_packet = hdr[0];
}