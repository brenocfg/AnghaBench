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
struct nfs_fh {int size; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4ERR_BADHANDLE ; 
 int /*<<< orphan*/  NFS4ERR_RESOURCE ; 
 int NFS4_FHSIZE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_buf (struct xdr_stream*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 decode_fh(struct xdr_stream *xdr, struct nfs_fh *fh)
{
	__be32 *p;

	p = read_buf(xdr, 4);
	if (unlikely(p == NULL))
		return htonl(NFS4ERR_RESOURCE);
	fh->size = ntohl(*p);
	if (fh->size > NFS4_FHSIZE)
		return htonl(NFS4ERR_BADHANDLE);
	p = read_buf(xdr, fh->size);
	if (unlikely(p == NULL))
		return htonl(NFS4ERR_RESOURCE);
	memcpy(&fh->data[0], p, fh->size);
	memset(&fh->data[fh->size], 0, sizeof(fh->data) - fh->size);
	return 0;
}