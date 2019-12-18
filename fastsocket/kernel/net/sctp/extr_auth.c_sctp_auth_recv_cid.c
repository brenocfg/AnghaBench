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
struct sctp_chunks_param {int dummy; } ;
struct TYPE_2__ {scalar_t__ auth_chunks; } ;
struct sctp_association {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  sctp_cid_t ;

/* Variables and functions */
 int __sctp_auth_cid (int /*<<< orphan*/ ,struct sctp_chunks_param*) ; 
 int /*<<< orphan*/  sctp_auth_enable ; 

int sctp_auth_recv_cid(sctp_cid_t chunk, const struct sctp_association *asoc)
{
	if (!sctp_auth_enable || !asoc)
		return 0;

	return __sctp_auth_cid(chunk,
			      (struct sctp_chunks_param *)asoc->c.auth_chunks);
}