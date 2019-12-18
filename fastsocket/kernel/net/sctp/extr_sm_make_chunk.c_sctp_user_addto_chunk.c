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
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int memcpy_fromiovecend (int /*<<< orphan*/ *,struct iovec*,int,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_put (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_tail_pointer (int /*<<< orphan*/ ) ; 

int sctp_user_addto_chunk(struct sctp_chunk *chunk, int off, int len,
			  struct iovec *data)
{
	__u8 *target;
	int err = 0;

	/* Make room in chunk for data.  */
	target = skb_put(chunk->skb, len);

	/* Copy data (whole iovec) into chunk */
	if ((err = memcpy_fromiovecend(target, data, off, len)))
		goto out;

	/* Adjust the chunk length field.  */
	chunk->chunk_hdr->length =
		htons(ntohs(chunk->chunk_hdr->length) + len);
	chunk->chunk_end = skb_tail_pointer(chunk->skb);

out:
	return err;
}