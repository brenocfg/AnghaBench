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
struct xdr_netobj {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * xdr_decode_netobj (int /*<<< orphan*/ *,struct xdr_netobj*) ; 

__attribute__((used)) static __be32 *
nlm4_decode_oh(__be32 *p, struct xdr_netobj *oh)
{
	return xdr_decode_netobj(p, oh);
}