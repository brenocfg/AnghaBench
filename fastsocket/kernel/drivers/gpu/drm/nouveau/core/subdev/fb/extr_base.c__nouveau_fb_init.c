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
struct nouveau_object {int dummy; } ;
struct nouveau_fb {int dummy; } ;

/* Variables and functions */
 int nouveau_fb_init (struct nouveau_fb*) ; 

int
_nouveau_fb_init(struct nouveau_object *object)
{
	struct nouveau_fb *pfb = (void *)object;
	return nouveau_fb_init(pfb);
}