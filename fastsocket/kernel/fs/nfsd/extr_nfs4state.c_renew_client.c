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
struct nfs4_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  client_lock ; 
 int /*<<< orphan*/  renew_client_locked (struct nfs4_client*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
renew_client(struct nfs4_client *clp)
{
	spin_lock(&client_lock);
	renew_client_locked(clp);
	spin_unlock(&client_lock);
}