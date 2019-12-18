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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct nouveau_mxm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_info (struct nouveau_mxm*,char*,int) ; 

__attribute__((used)) static bool
mxm_show_unmatched(struct nouveau_mxm *mxm, u8 *data, void *info)
{
	u64 desc = *(u64 *)data;
	if ((desc & 0xf0) != 0xf0)
	nv_info(mxm, "unmatched output device 0x%016llx\n", desc);
	return true;
}