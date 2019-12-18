#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long num_chunks; int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 scalar_t__ _ALIGN (scalar_t__,int) ; 
 scalar_t__ klimit ; 
 TYPE_1__ mschunks_map ; 

__attribute__((used)) static void mschunks_alloc(unsigned long num_chunks)
{
	klimit = _ALIGN(klimit, sizeof(u32));
	mschunks_map.mapping = (u32 *)klimit;
	klimit += num_chunks * sizeof(u32);
	mschunks_map.num_chunks = num_chunks;
}