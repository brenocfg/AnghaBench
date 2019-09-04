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
struct pfr_ktable {int /*<<< orphan*/  pfrkt_anchor; int /*<<< orphan*/  pfrkt_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_TABLE_NAME_SIZE ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfr_ktable_compare(struct pfr_ktable *p, struct pfr_ktable *q)
{
	int d;

	if ((d = strncmp(p->pfrkt_name, q->pfrkt_name, PF_TABLE_NAME_SIZE)))
		return (d);
	return (strcmp(p->pfrkt_anchor, q->pfrkt_anchor));
}