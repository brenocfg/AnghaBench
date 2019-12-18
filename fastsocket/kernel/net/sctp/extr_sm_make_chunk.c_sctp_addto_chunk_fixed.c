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
struct sctp_chunk {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 void* sctp_addto_chunk (struct sctp_chunk*,int,void const*) ; 
 int skb_tailroom (int /*<<< orphan*/ ) ; 

void *sctp_addto_chunk_fixed(struct sctp_chunk *chunk,
			     int len, const void *data)
{
	if (skb_tailroom(chunk->skb) >= len)
		return sctp_addto_chunk(chunk, len, data);
	else
		return NULL;
}