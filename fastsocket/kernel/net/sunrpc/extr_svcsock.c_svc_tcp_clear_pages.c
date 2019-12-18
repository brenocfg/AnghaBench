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
struct svc_sock {int sk_tcplen; int /*<<< orphan*/ ** sk_pages; } ;
typedef  int /*<<< orphan*/  rpc_fraghdr ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void svc_tcp_clear_pages(struct svc_sock *svsk)
{
	unsigned int i, len, npages;

	if (svsk->sk_tcplen <= sizeof(rpc_fraghdr))
		goto out;
	len = svsk->sk_tcplen - sizeof(rpc_fraghdr);
	npages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	for (i = 0; i < npages; i++) {
		BUG_ON(svsk->sk_pages[i] == NULL);
		put_page(svsk->sk_pages[i]);
		svsk->sk_pages[i] = NULL;
	}
out:
	svsk->sk_tcplen = 0;
}