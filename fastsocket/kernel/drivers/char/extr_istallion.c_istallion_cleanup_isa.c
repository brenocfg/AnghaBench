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
struct stlibrd {int state; scalar_t__ iosize; int /*<<< orphan*/  iobase; int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int BST_PROBED ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct stlibrd*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,scalar_t__) ; 
 struct stlibrd** stli_brds ; 
 int /*<<< orphan*/  stli_cleanup_ports (struct stlibrd*) ; 
 unsigned int stli_nrbrds ; 

__attribute__((used)) static void istallion_cleanup_isa(void)
{
	struct stlibrd	*brdp;
	unsigned int j;

	for (j = 0; (j < stli_nrbrds); j++) {
		if ((brdp = stli_brds[j]) == NULL || (brdp->state & BST_PROBED))
			continue;

		stli_cleanup_ports(brdp);

		iounmap(brdp->membase);
		if (brdp->iosize > 0)
			release_region(brdp->iobase, brdp->iosize);
		kfree(brdp);
		stli_brds[j] = NULL;
	}
}