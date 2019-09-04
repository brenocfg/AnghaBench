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
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  AddAllChainCertsToCertList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AddAllRootCertsToCertList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewList (int /*<<< orphan*/ *) ; 

LIST *NewCertList(bool load_root_and_chain)
{
	LIST *o;

	o = NewList(NULL);

	if (load_root_and_chain)
	{
		AddAllRootCertsToCertList(o);
		AddAllChainCertsToCertList(o);
	}

	return o;
}