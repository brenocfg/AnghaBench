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
struct vc_data {unsigned long* vc_uni_pagedir_loc; } ;
struct unimapinit {int dummy; } ;
struct uni_pagedir {int refcount; scalar_t__ sum; scalar_t__ readonly; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  con_release_unimap (struct uni_pagedir*) ; 
 struct uni_pagedir* dflt ; 
 struct uni_pagedir* kzalloc (int,int /*<<< orphan*/ ) ; 

int con_clear_unimap(struct vc_data *vc, struct unimapinit *ui)
{
	struct uni_pagedir *p, *q;
  
	p = (struct uni_pagedir *)*vc->vc_uni_pagedir_loc;
	if (p && p->readonly) return -EIO;
	if (!p || --p->refcount) {
		q = kzalloc(sizeof(*p), GFP_KERNEL);
		if (!q) {
			if (p) p->refcount++;
			return -ENOMEM;
		}
		q->refcount=1;
		*vc->vc_uni_pagedir_loc = (unsigned long)q;
	} else {
		if (p == dflt) dflt = NULL;
		p->refcount++;
		p->sum = 0;
		con_release_unimap(p);
	}
	return 0;
}