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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct nouveau_mxm {int dummy; } ;

/* Variables and functions */
 scalar_t__* mxms_data (struct nouveau_mxm*) ; 
 scalar_t__ mxms_headerlen (struct nouveau_mxm*) ; 
 scalar_t__ mxms_structlen (struct nouveau_mxm*) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_mxm*,char*) ; 

bool
mxms_checksum(struct nouveau_mxm *mxm)
{
	u16 size = mxms_headerlen(mxm) + mxms_structlen(mxm);
	u8 *mxms = mxms_data(mxm), sum = 0;
	while (size--)
		sum += *mxms++;
	if (sum) {
		nv_debug(mxm, "checksum invalid\n");
		return false;
	}
	return true;
}