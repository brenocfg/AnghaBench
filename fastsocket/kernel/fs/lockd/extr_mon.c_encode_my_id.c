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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int dummy; } ;
struct nsm_args {int /*<<< orphan*/  proc; int /*<<< orphan*/  vers; int /*<<< orphan*/  prog; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int EIO ; 
 int encode_nsm_string (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__* utsname () ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static int encode_my_id(struct xdr_stream *xdr, const struct nsm_args *argp)
{
	int status;
	__be32 *p;

	status = encode_nsm_string(xdr, utsname()->nodename);
	if (unlikely(status != 0))
		return status;
	p = xdr_reserve_space(xdr, 3 * sizeof(u32));
	if (unlikely(p == NULL))
		return -EIO;
	*p++ = htonl(argp->prog);
	*p++ = htonl(argp->vers);
	*p++ = htonl(argp->proc);
	return 0;
}