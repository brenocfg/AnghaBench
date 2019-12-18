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
struct scatter_walk {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_pagedone (struct scatter_walk*,int,int) ; 

void scatterwalk_done(struct scatter_walk *walk, int out, int more)
{
	if (!offset_in_page(walk->offset) || !more)
		scatterwalk_pagedone(walk, out, more);
}