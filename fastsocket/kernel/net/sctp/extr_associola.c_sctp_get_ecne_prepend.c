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
struct sctp_chunk {int dummy; } ;
struct sctp_association {int /*<<< orphan*/  last_ecne_tsn; scalar_t__ need_ecne; } ;

/* Variables and functions */
 struct sctp_chunk* sctp_make_ecne (struct sctp_association*,int /*<<< orphan*/ ) ; 

struct sctp_chunk *sctp_get_ecne_prepend(struct sctp_association *asoc)
{
	struct sctp_chunk *chunk;

	/* Send ECNE if needed.
	 * Not being able to allocate a chunk here is not deadly.
	 */
	if (asoc->need_ecne)
		chunk = sctp_make_ecne(asoc, asoc->last_ecne_tsn);
	else
		chunk = NULL;

	return chunk;
}