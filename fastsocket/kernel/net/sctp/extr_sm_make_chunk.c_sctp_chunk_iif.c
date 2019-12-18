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
struct sctp_chunk {int /*<<< orphan*/  skb; } ;
struct sctp_af {int (* skb_iif ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 TYPE_1__* ip_hdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipver2af (int /*<<< orphan*/ ) ; 
 struct sctp_af* sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int sctp_chunk_iif(const struct sctp_chunk *chunk)
{
	struct sctp_af *af;
	int iif = 0;

	af = sctp_get_af_specific(ipver2af(ip_hdr(chunk->skb)->version));
	if (af)
		iif = af->skb_iif(chunk->skb);

	return iif;
}