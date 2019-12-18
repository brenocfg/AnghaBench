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
struct nouveau_ramht {int dummy; } ;
struct nouveau_bar {int /*<<< orphan*/  (* flush ) (struct nouveau_bar*) ;} ;

/* Variables and functions */
 struct nouveau_bar* nouveau_bar (struct nouveau_ramht*) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_ramht*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bar*) ; 

void
nouveau_ramht_remove(struct nouveau_ramht *ramht, int cookie)
{
	struct nouveau_bar *bar = nouveau_bar(ramht);
	nv_wo32(ramht, cookie + 0, 0x00000000);
	nv_wo32(ramht, cookie + 4, 0x00000000);
	if (bar)
		bar->flush(bar);
}