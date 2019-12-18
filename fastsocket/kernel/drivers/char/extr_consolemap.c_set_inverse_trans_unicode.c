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
typedef  int u16 ;
struct vc_data {int dummy; } ;
struct uni_pagedir {int* inverse_trans_unicode; int*** uni_pgdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_GLYPH ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_inverse_trans_unicode(struct vc_data *conp,
				      struct uni_pagedir *p)
{
	int i, j, k, glyph;
	u16 **p1, *p2;
	u16 *q;

	if (!p) return;
	q = p->inverse_trans_unicode;
	if (!q) {
		q = p->inverse_trans_unicode =
			kmalloc(MAX_GLYPH * sizeof(u16), GFP_KERNEL);
		if (!q)
			return;
	}
	memset(q, 0, MAX_GLYPH * sizeof(u16));

	for (i = 0; i < 32; i++) {
		p1 = p->uni_pgdir[i];
		if (!p1)
			continue;
		for (j = 0; j < 32; j++) {
			p2 = p1[j];
			if (!p2)
				continue;
			for (k = 0; k < 64; k++) {
				glyph = p2[k];
				if (glyph >= 0 && glyph < MAX_GLYPH
					       && q[glyph] < 32)
		  			q[glyph] = (i << 11) + (j << 6) + k;
			}
		}
	}
}