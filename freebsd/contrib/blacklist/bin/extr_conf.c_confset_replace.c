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
struct confset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  confset_free (struct confset*) ; 
 int /*<<< orphan*/  confset_init (struct confset*) ; 

__attribute__((used)) static void
confset_replace(struct confset *dc, struct confset *sc)
{
	struct confset tc;
	tc = *dc;
	*dc = *sc;
	confset_init(sc);
	confset_free(&tc);
}