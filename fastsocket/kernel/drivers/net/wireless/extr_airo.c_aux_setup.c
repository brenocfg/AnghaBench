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
struct airo_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXDATA ; 
 int /*<<< orphan*/  AUXOFF ; 
 int /*<<< orphan*/  AUXPAGE ; 
 int IN4500 (struct airo_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 aux_setup(struct airo_info *ai, u16 page,
		     u16 offset, u16 *len)
{
	u16 next;

	OUT4500(ai, AUXPAGE, page);
	OUT4500(ai, AUXOFF, 0);
	next = IN4500(ai, AUXDATA);
	*len = IN4500(ai, AUXDATA)&0xff;
	if (offset != 4) OUT4500(ai, AUXOFF, offset);
	return next;
}