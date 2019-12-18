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
typedef  int /*<<< orphan*/  u_char ;
struct IsdnCardState {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFCD_DATA ; 
 int /*<<< orphan*/  ReadReg (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char
readreghfcd(struct IsdnCardState *cs, u_char offset)
{
	return(ReadReg(cs, HFCD_DATA, offset));
}