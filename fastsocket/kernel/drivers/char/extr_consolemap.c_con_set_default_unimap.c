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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {unsigned long* vc_uni_pagedir_loc; } ;
struct uni_pagedir {scalar_t__ refcount; } ;

/* Variables and functions */
 int con_clear_unimap (struct vc_data*,int /*<<< orphan*/ *) ; 
 int con_insert_unipair (struct uni_pagedir*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  con_release_unimap (struct uni_pagedir*) ; 
 scalar_t__ con_unify_unimap (struct vc_data*,struct uni_pagedir*) ; 
 struct uni_pagedir* dflt ; 
 int* dfont_unicount ; 
 int /*<<< orphan*/ * dfont_unitable ; 
 int /*<<< orphan*/  kfree (struct uni_pagedir*) ; 
 int /*<<< orphan*/  set_inverse_trans_unicode (struct vc_data*,struct uni_pagedir*) ; 
 int /*<<< orphan*/  set_inverse_transl (struct vc_data*,struct uni_pagedir*,int) ; 

int con_set_default_unimap(struct vc_data *vc)
{
	int i, j, err = 0, err1;
	u16 *q;
	struct uni_pagedir *p;

	if (dflt) {
		p = (struct uni_pagedir *)*vc->vc_uni_pagedir_loc;
		if (p == dflt)
			return 0;
		dflt->refcount++;
		*vc->vc_uni_pagedir_loc = (unsigned long)dflt;
		if (p && --p->refcount) {
			con_release_unimap(p);
			kfree(p);
		}
		return 0;
	}
	
	/* The default font is always 256 characters */

	err = con_clear_unimap(vc, NULL);
	if (err) return err;
    
	p = (struct uni_pagedir *)*vc->vc_uni_pagedir_loc;
	q = dfont_unitable;
	
	for (i = 0; i < 256; i++)
		for (j = dfont_unicount[i]; j; j--) {
			err1 = con_insert_unipair(p, *(q++), i);
			if (err1)
				err = err1;
		}
			
	if (con_unify_unimap(vc, p)) {
		dflt = (struct uni_pagedir *)*vc->vc_uni_pagedir_loc;
		return err;
	}

	for (i = 0; i <= 3; i++)
		set_inverse_transl(vc, p, i);	/* Update all inverse translations */
	set_inverse_trans_unicode(vc, p);
	dflt = p;
	return err;
}