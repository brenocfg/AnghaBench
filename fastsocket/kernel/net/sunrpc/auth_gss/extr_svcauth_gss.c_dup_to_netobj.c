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
struct xdr_netobj {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmemdup (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dup_to_netobj(struct xdr_netobj *dst, char *src, int len)
{
	dst->len = len;
	dst->data = (len ? kmemdup(src, len, GFP_KERNEL) : NULL);
	if (len && !dst->data)
		return -ENOMEM;
	return 0;
}