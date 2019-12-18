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
struct rpc_rqst {int /*<<< orphan*/  rq_snd_buf; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int encode_mntdirpath (struct xdr_stream*,char const*) ; 
 int /*<<< orphan*/  xdr_init_encode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mnt_enc_dirpath(struct rpc_rqst *req, __be32 *p,
			   const char *dirpath)
{
	struct xdr_stream xdr;

	xdr_init_encode(&xdr, &req->rq_snd_buf, p);
	return encode_mntdirpath(&xdr, dirpath);
}