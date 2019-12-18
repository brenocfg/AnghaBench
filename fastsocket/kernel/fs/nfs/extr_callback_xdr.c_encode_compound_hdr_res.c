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
struct cb_compound_hdr_res {int /*<<< orphan*/ * nops; int /*<<< orphan*/  tag; int /*<<< orphan*/  taglen; int /*<<< orphan*/ * status; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4ERR_RESOURCE ; 
 scalar_t__ encode_string (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 void* xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32 encode_compound_hdr_res(struct xdr_stream *xdr, struct cb_compound_hdr_res *hdr)
{
	__be32 status;

	hdr->status = xdr_reserve_space(xdr, 4);
	if (unlikely(hdr->status == NULL))
		return htonl(NFS4ERR_RESOURCE);
	status = encode_string(xdr, hdr->taglen, hdr->tag);
	if (unlikely(status != 0))
		return status;
	hdr->nops = xdr_reserve_space(xdr, 4);
	if (unlikely(hdr->nops == NULL))
		return htonl(NFS4ERR_RESOURCE);
	return 0;
}