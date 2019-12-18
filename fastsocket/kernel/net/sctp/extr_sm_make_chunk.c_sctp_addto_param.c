#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sctp_chunk {int /*<<< orphan*/  skb; int /*<<< orphan*/  chunk_end; TYPE_1__* chunk_hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 void* skb_put (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_tail_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *sctp_addto_param(struct sctp_chunk *chunk, int len,
			      const void *data)
{
	void *target;
	int chunklen = ntohs(chunk->chunk_hdr->length);

	target = skb_put(chunk->skb, len);

	if (data)
		memcpy(target, data, len);
	else
		memset(target, 0, len);

	/* Adjust the chunk length field.  */
	chunk->chunk_hdr->length = htons(chunklen + len);
	chunk->chunk_end = skb_tail_pointer(chunk->skb);

	return target;
}