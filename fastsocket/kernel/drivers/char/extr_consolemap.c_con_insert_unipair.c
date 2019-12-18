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
typedef  int u_short ;
typedef  int u16 ;
struct uni_pagedir {int*** uni_pgdir; int sum; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static int
con_insert_unipair(struct uni_pagedir *p, u_short unicode, u_short fontpos)
{
	int i, n;
	u16 **p1, *p2;

	if (!(p1 = p->uni_pgdir[n = unicode >> 11])) {
		p1 = p->uni_pgdir[n] = kmalloc(32*sizeof(u16 *), GFP_KERNEL);
		if (!p1) return -ENOMEM;
		for (i = 0; i < 32; i++)
			p1[i] = NULL;
	}

	if (!(p2 = p1[n = (unicode >> 6) & 0x1f])) {
		p2 = p1[n] = kmalloc(64*sizeof(u16), GFP_KERNEL);
		if (!p2) return -ENOMEM;
		memset(p2, 0xff, 64*sizeof(u16)); /* No glyphs for the characters (yet) */
	}

	p2[unicode & 0x3f] = fontpos;
	
	p->sum += (fontpos << 20) + unicode;

	return 0;
}