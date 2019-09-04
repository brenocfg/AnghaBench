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
typedef  scalar_t__ commpage_address_t ;

/* Variables and functions */
 scalar_t__ commPageBaseOffset ; 
 scalar_t__ commPagePtr ; 

__attribute__((used)) static void*
commpage_addr_of(
    commpage_address_t     addr_at_runtime )
{
	return  (void*) ((uintptr_t)commPagePtr + (addr_at_runtime - commPageBaseOffset));
}