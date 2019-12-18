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
struct cred {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdebug (char*,struct cred*,int,scalar_t__) ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 scalar_t__ read_cred_subscribers (struct cred*) ; 

void abort_creds(struct cred *new)
{
	kdebug("abort_creds(%p{%d,%d})", new,
	       atomic_read(&new->usage),
	       read_cred_subscribers(new));

#ifdef CONFIG_DEBUG_CREDENTIALS
	BUG_ON(read_cred_subscribers(new) != 0);
#endif
	BUG_ON(atomic_read(&new->usage) < 1);
	put_cred(new);
}