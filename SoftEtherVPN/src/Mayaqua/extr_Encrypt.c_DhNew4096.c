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
typedef  int /*<<< orphan*/  DH_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DH_SET_4096 ; 
 int /*<<< orphan*/ * DhNew (int /*<<< orphan*/ ,int) ; 

DH_CTX *DhNew4096()
{
	return DhNew(DH_SET_4096, 2);
}