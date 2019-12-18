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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_encode_opaque (int /*<<< orphan*/ *,char const*,unsigned int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_string(struct xdr_stream *xdr, unsigned int len, const char *str)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 + len);
	BUG_ON(p == NULL);
	xdr_encode_opaque(p, str, len);
}