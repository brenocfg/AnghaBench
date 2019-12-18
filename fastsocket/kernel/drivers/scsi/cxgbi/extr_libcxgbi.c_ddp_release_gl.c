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
struct pci_dev {int dummy; } ;
struct cxgbi_gather_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddp_gl_unmap (struct pci_dev*,struct cxgbi_gather_list*) ; 
 int /*<<< orphan*/  kfree (struct cxgbi_gather_list*) ; 

__attribute__((used)) static void ddp_release_gl(struct cxgbi_gather_list *gl,
				  struct pci_dev *pdev)
{
	ddp_gl_unmap(pdev, gl);
	kfree(gl);
}