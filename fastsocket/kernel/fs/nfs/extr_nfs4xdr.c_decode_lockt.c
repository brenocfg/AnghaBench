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
struct xdr_stream {int dummy; } ;
struct nfs_lockt_res {int /*<<< orphan*/  denied; } ;

/* Variables and functions */
 int NFS4ERR_DENIED ; 
 int /*<<< orphan*/  OP_LOCKT ; 
 int decode_lock_denied (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int decode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_lockt(struct xdr_stream *xdr, struct nfs_lockt_res *res)
{
	int status;
	status = decode_op_hdr(xdr, OP_LOCKT);
	if (status == -NFS4ERR_DENIED)
		return decode_lock_denied(xdr, res->denied);
	return status;
}