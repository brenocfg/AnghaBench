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
struct ipr_sglist {int num_sg; int /*<<< orphan*/  order; int /*<<< orphan*/ * scatterlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipr_sglist*) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_free_ucode_buffer(struct ipr_sglist *sglist)
{
	int i;

	for (i = 0; i < sglist->num_sg; i++)
		__free_pages(sg_page(&sglist->scatterlist[i]), sglist->order);

	kfree(sglist);
}