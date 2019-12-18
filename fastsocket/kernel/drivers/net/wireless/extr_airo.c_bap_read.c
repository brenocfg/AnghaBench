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
struct airo_info {int (* bap_read ) (struct airo_info*,int /*<<< orphan*/ *,int,int) ;} ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int stub1 (struct airo_info*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int bap_read(struct airo_info *ai, __le16 *pu16Dst, int bytelen,
			   int whichbap)
{
	return ai->bap_read(ai, pu16Dst, bytelen, whichbap);
}