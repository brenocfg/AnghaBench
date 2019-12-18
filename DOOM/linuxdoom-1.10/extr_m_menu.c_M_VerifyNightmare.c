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

/* Variables and functions */
 int /*<<< orphan*/  G_DeferedInitNew (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  M_ClearMenus () ; 
 scalar_t__ epi ; 
 int /*<<< orphan*/  nightmare ; 

void M_VerifyNightmare(int ch)
{
    if (ch != 'y')
	return;
		
    G_DeferedInitNew(nightmare,epi+1,1);
    M_ClearMenus ();
}