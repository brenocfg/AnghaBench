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
struct scatterlist {int /*<<< orphan*/  offset; int /*<<< orphan*/  length; } ;
struct scatter_walk {int /*<<< orphan*/  offset; struct scatterlist* sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

void scatterwalk_start(struct scatter_walk *walk, struct scatterlist *sg)
{
	walk->sg = sg;

	BUG_ON(!sg->length);

	walk->offset = sg->offset;
}