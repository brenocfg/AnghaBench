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
struct xdr_netobj {scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__) ; 

__attribute__((used)) static int check_name(struct xdr_netobj name)
{
	if (name.len == 0) 
		return 0;
	if (name.len > NFS4_OPAQUE_LIMIT) {
		dprintk("NFSD: check_name: name too long(%d)!\n", name.len);
		return 0;
	}
	return 1;
}