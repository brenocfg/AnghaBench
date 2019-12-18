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
struct nfs_fattr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * xdr_decode_wcc_attr (int /*<<< orphan*/ *,struct nfs_fattr*) ; 

__attribute__((used)) static inline __be32 *
xdr_decode_pre_op_attr(__be32 *p, struct nfs_fattr *fattr)
{
	if (*p++)
		return xdr_decode_wcc_attr(p, fattr);
	return p;
}