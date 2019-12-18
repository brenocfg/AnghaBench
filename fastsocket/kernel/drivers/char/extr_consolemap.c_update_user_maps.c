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
struct uni_pagedir {int dummy; } ;
struct TYPE_5__ {scalar_t__* vc_uni_pagedir_loc; } ;
struct TYPE_4__ {TYPE_2__* d; } ;

/* Variables and functions */
 int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  USER_MAP ; 
 int /*<<< orphan*/  set_inverse_trans_unicode (TYPE_2__*,struct uni_pagedir*) ; 
 int /*<<< orphan*/  set_inverse_transl (TYPE_2__*,struct uni_pagedir*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vc_cons ; 
 int /*<<< orphan*/  vc_cons_allocated (int) ; 

__attribute__((used)) static void update_user_maps(void)
{
	int i;
	struct uni_pagedir *p, *q = NULL;
	
	for (i = 0; i < MAX_NR_CONSOLES; i++) {
		if (!vc_cons_allocated(i))
			continue;
		p = (struct uni_pagedir *)*vc_cons[i].d->vc_uni_pagedir_loc;
		if (p && p != q) {
			set_inverse_transl(vc_cons[i].d, p, USER_MAP);
			set_inverse_trans_unicode(vc_cons[i].d, p);
			q = p;
		}
	}
}