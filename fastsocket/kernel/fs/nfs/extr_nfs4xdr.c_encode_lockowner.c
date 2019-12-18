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
struct nfs_lowner {int s_dev; int /*<<< orphan*/  id; int /*<<< orphan*/  clientid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void encode_lockowner(struct xdr_stream *xdr, const struct nfs_lowner *lowner)
{
	__be32 *p;

	p = reserve_space(xdr, 32);
	p = xdr_encode_hyper(p, lowner->clientid);
	*p++ = cpu_to_be32(20);
	p = xdr_encode_opaque_fixed(p, "lock id:", 8);
	*p++ = cpu_to_be32(lowner->s_dev);
	xdr_encode_hyper(p, lowner->id);
}