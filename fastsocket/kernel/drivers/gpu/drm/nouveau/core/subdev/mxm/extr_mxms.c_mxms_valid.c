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
typedef  int u32 ;
struct nouveau_mxm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxms_checksum (struct nouveau_mxm*) ; 
 int /*<<< orphan*/ * mxms_data (struct nouveau_mxm*) ; 
 int /*<<< orphan*/  mxms_version (struct nouveau_mxm*) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_mxm*,char*) ; 

bool
mxms_valid(struct nouveau_mxm *mxm)
{
	u8 *mxms = mxms_data(mxm);
	if (*(u32 *)mxms != 0x5f4d584d) {
		nv_debug(mxm, "signature invalid\n");
		return false;
	}

	if (!mxms_version(mxm) || !mxms_checksum(mxm))
		return false;

	return true;
}