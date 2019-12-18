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
struct nfsd4_conn {int /*<<< orphan*/  cn_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfsd4_conn*) ; 
 int /*<<< orphan*/  svc_xprt_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_conn(struct nfsd4_conn *c)
{
	svc_xprt_put(c->cn_xprt);
	kfree(c);
}