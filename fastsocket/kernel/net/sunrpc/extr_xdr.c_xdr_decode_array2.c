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
struct xdr_buf {unsigned int len; } ;
struct xdr_array2_desc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int xdr_xcode_array2 (struct xdr_buf*,unsigned int,struct xdr_array2_desc*,int /*<<< orphan*/ ) ; 

int
xdr_decode_array2(struct xdr_buf *buf, unsigned int base,
		  struct xdr_array2_desc *desc)
{
	if (base >= buf->len)
		return -EINVAL;

	return xdr_xcode_array2(buf, base, desc, 0);
}