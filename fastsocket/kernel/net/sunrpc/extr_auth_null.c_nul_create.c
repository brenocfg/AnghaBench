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
struct rpc_clnt {int dummy; } ;
struct rpc_auth {int /*<<< orphan*/  au_count; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct rpc_auth null_auth ; 

__attribute__((used)) static struct rpc_auth *
nul_create(struct rpc_clnt *clnt, rpc_authflavor_t flavor)
{
	atomic_inc(&null_auth.au_count);
	return &null_auth;
}