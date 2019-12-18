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
struct nfs4_change_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_LINK ; 
 int decode_change_info (struct xdr_stream*,struct nfs4_change_info*) ; 
 int decode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_link(struct xdr_stream *xdr, struct nfs4_change_info *cinfo)
{
	int status;

	status = decode_op_hdr(xdr, OP_LINK);
	if (status)
		return status;
	return decode_change_info(xdr, cinfo);
}