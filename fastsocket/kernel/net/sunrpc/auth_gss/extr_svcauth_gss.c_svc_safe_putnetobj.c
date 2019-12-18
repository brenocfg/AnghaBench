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
typedef  int /*<<< orphan*/  u8 ;
struct xdr_netobj {int len; int /*<<< orphan*/  data; } ;
struct kvec {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int round_up_to_quad (int) ; 
 int /*<<< orphan*/  svc_putnl (struct kvec*,int) ; 

__attribute__((used)) static inline int
svc_safe_putnetobj(struct kvec *resv, struct xdr_netobj *o)
{
	u8 *p;

	if (resv->iov_len + 4 > PAGE_SIZE)
		return -1;
	svc_putnl(resv, o->len);
	p = resv->iov_base + resv->iov_len;
	resv->iov_len += round_up_to_quad(o->len);
	if (resv->iov_len > PAGE_SIZE)
		return -1;
	memcpy(p, o->data, o->len);
	memset(p + o->len, 0, round_up_to_quad(o->len) - o->len);
	return 0;
}