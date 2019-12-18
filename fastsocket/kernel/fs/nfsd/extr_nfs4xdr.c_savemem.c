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
struct nfsd4_compoundargs {int /*<<< orphan*/ * tmpp; int /*<<< orphan*/ * tmp; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ defer_free (struct nfsd4_compoundargs*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *savemem(struct nfsd4_compoundargs *argp, __be32 *p, int nbytes)
{
	if (p == argp->tmp) {
		p = kmalloc(nbytes, GFP_KERNEL);
		if (!p)
			return NULL;
		memcpy(p, argp->tmp, nbytes);
	} else {
		BUG_ON(p != argp->tmpp);
		argp->tmpp = NULL;
	}
	if (defer_free(argp, kfree, p)) {
		kfree(p);
		return NULL;
	} else
		return (char *)p;
}