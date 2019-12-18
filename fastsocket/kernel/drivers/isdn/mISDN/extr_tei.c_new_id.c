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
typedef  int u_int ;
struct manager {int nextid; } ;

/* Variables and functions */
 int GROUP_TEI ; 
 int TEI_SAPI ; 

__attribute__((used)) static u_int
new_id(struct manager *mgr)
{
	u_int	id;

	id = mgr->nextid++;
	if (id == 0x7fff)
		mgr->nextid = 1;
	id <<= 16;
	id |= GROUP_TEI << 8;
	id |= TEI_SAPI;
	return id;
}