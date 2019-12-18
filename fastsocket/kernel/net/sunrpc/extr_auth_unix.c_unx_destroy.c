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
struct rpc_auth {int /*<<< orphan*/  au_credcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct rpc_auth*) ; 
 int /*<<< orphan*/  rpcauth_clear_credcache (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unx_destroy(struct rpc_auth *auth)
{
	dprintk("RPC:       destroying UNIX authenticator %p\n", auth);
	rpcauth_clear_credcache(auth->au_credcache);
}