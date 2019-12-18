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
typedef  int UINT ;
typedef  int /*<<< orphan*/  DH_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * DhNew2048 () ; 
 int /*<<< orphan*/ * DhNew3072 () ; 
 int /*<<< orphan*/ * DhNew4096 () ; 
 int /*<<< orphan*/ * DhNewGroup1 () ; 
 int /*<<< orphan*/ * DhNewGroup2 () ; 
 int /*<<< orphan*/ * DhNewGroup5 () ; 
 int /*<<< orphan*/ * DhNewSimple160 () ; 

DH_CTX *DhNewFromBits(UINT bits)
{
	switch (bits)
	{
	case 160:
		return DhNewSimple160();
	case 768:
		return DhNewGroup1();
	case 1024:
		return DhNewGroup2();
	case 1536:
		return DhNewGroup5();
	case 2048:
		return DhNew2048();
	case 3072:
		return DhNew3072();
	case 4096:
		return DhNew4096();
	default:
		return DhNew2048();
	}
}