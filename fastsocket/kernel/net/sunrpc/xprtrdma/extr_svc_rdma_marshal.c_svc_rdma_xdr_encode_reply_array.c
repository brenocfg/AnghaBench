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
struct rpcrdma_write_array {int /*<<< orphan*/  wc_nchunks; int /*<<< orphan*/  wc_discrim; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  xdr_one ; 

void svc_rdma_xdr_encode_reply_array(struct rpcrdma_write_array *ary,
				 int chunks)
{
	ary->wc_discrim = xdr_one;
	ary->wc_nchunks = htonl(chunks);
}