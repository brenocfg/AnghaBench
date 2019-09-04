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
struct pf_anchor {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
pf_anchor_compare(struct pf_anchor *a, struct pf_anchor *b)
{
	int c = strcmp(a->path, b->path);

	return (c ? (c < 0 ? -1 : 1) : 0);
}