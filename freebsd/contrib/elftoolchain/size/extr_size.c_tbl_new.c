#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int col; scalar_t__ row; int /*<<< orphan*/ * width; int /*<<< orphan*/ * tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* tb ; 

__attribute__((used)) static void
tbl_new(int col)
{

	assert(tb == NULL);
	assert(col > 0);
	if ((tb = calloc(1, sizeof(*tb))) == NULL)
		err(EXIT_FAILURE, "calloc");
	if ((tb->tbl = calloc(col, sizeof(*tb->tbl))) == NULL)
		err(EXIT_FAILURE, "calloc");
	if ((tb->width = calloc(col, sizeof(*tb->width))) == NULL)
		err(EXIT_FAILURE, "calloc");
	tb->col = col;
	tb->row = 0;
}