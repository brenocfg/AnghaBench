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
struct gds_subvector {int length; int key; } ;

/* Variables and functions */
 int /*<<< orphan*/  sclp_get_input (struct gds_subvector*) ; 

__attribute__((used)) static inline void sclp_eval_selfdeftextmsg(struct gds_subvector *sv)
{
	void *end;

	end = (void *) sv + sv->length;
	for (sv = sv + 1; (void *) sv < end; sv = (void *) sv + sv->length)
		if (sv->key == 0x30)
			sclp_get_input(sv);
}