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
struct TYPE_2__ {int col; int row; int* width; int /*<<< orphan*/ *** tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int strlen (char const*) ; 
 TYPE_1__* tb ; 

__attribute__((used)) static void
tbl_print(const char *s, int col)
{
	int len;

	assert(tb != NULL && tb->col > 0 && tb->row > 0 && col < tb->col);
	assert(s != NULL && tb->tbl[col][tb->row - 1] == NULL);
	if ((tb->tbl[col][tb->row - 1] = strdup(s)) == NULL)
		err(EXIT_FAILURE, "strdup");
	len = strlen(s);
	if (len > tb->width[col])
		tb->width[col] = len;
}