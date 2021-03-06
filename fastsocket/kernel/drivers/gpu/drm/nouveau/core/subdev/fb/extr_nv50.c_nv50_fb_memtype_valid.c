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
typedef  int u32 ;
struct nouveau_fb {int dummy; } ;

/* Variables and functions */
 scalar_t__* types ; 

__attribute__((used)) static bool
nv50_fb_memtype_valid(struct nouveau_fb *pfb, u32 memtype)
{
	return types[(memtype & 0xff00) >> 8] != 0;
}