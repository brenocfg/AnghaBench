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
struct sctp_auth_bytes {int dummy; } ;
struct TYPE_2__ {scalar_t__ auth_hmacs; scalar_t__ auth_chunks; scalar_t__ auth_random; } ;
struct sctp_association {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  sctp_random_param_t ;
typedef  int /*<<< orphan*/  sctp_hmac_algo_param_t ;
typedef  int /*<<< orphan*/  sctp_chunks_param_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct sctp_auth_bytes* sctp_auth_make_key_vector (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_auth_bytes *sctp_auth_make_local_vector(
				    const struct sctp_association *asoc,
				    gfp_t gfp)
{
	return sctp_auth_make_key_vector(
				    (sctp_random_param_t*)asoc->c.auth_random,
				    (sctp_chunks_param_t*)asoc->c.auth_chunks,
				    (sctp_hmac_algo_param_t*)asoc->c.auth_hmacs,
				    gfp);
}