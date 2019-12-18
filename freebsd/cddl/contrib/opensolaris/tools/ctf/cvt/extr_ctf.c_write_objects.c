#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort_t ;
struct TYPE_5__ {char* ii_name; TYPE_1__* ii_dtype; } ;
typedef  TYPE_2__ iidesc_t ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  ctf_buf_t ;
struct TYPE_4__ {int /*<<< orphan*/  t_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_buf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debug (int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ target_requires_swap ; 

__attribute__((used)) static void
write_objects(iidesc_t *idp, ctf_buf_t *b)
{
	ushort_t id = (idp ? idp->ii_dtype->t_id : 0);

	if (target_requires_swap) {
		SWAP_16(id);
	}

	ctf_buf_write(b, &id, sizeof (id));

	debug(3, "Wrote object %s (%d)\n", (idp ? idp->ii_name : "(null)"), id);
}