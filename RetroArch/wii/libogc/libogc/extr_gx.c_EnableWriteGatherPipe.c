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
 int mfhid2 () ; 
 int /*<<< orphan*/  mthid2 (int) ; 
 int /*<<< orphan*/  mtwpar (int) ; 

__attribute__((used)) static __inline__ void EnableWriteGatherPipe()
{
	mtwpar(0x0C008000);
	mthid2((mfhid2()|0x40000000));
}