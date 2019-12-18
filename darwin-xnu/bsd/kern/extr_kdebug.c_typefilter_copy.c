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
typedef  int /*<<< orphan*/ * typefilter_t ;

/* Variables and functions */
 int /*<<< orphan*/  KDBG_TYPEFILTER_BITMAP_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void typefilter_copy(typefilter_t dst, typefilter_t src)
{
	assert(src != NULL);
	assert(dst != NULL);
	memcpy(dst, src, KDBG_TYPEFILTER_BITMAP_SIZE);
}