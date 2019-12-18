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
typedef  scalar_t__ aid_t ;
typedef  int /*<<< orphan*/  SInt64 ;

/* Variables and functions */
 scalar_t__ OSIncrementAtomic64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_aid ; 

__attribute__((used)) static aid_t
get_aid()
{
	aid_t aid;
	aid = (aid_t)OSIncrementAtomic64((SInt64 *)&global_aid);
	return aid;
}