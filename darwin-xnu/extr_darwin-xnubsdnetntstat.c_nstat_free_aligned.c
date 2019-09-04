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
typedef  int /*<<< orphan*/  u_int8_t ;
struct align_header {int offset; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  OSMallocTag ;

/* Variables and functions */
 int /*<<< orphan*/  OSFree (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nstat_free_aligned(
	void		*buffer,
	OSMallocTag	tag)
{
	struct align_header *hdr = (struct align_header*)(void *)((u_int8_t*)buffer - sizeof(*hdr));
	OSFree(((char*)buffer) - hdr->offset, hdr->length, tag);
}