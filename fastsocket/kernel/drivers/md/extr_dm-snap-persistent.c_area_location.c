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
struct pstore {int exceptions_per_area; } ;
typedef  int chunk_t ;

/* Variables and functions */
 int NUM_SNAPSHOT_HDR_CHUNKS ; 

__attribute__((used)) static chunk_t area_location(struct pstore *ps, chunk_t area)
{
	return NUM_SNAPSHOT_HDR_CHUNKS + ((ps->exceptions_per_area + 1) * area);
}