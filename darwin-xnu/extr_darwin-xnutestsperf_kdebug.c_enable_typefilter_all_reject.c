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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  type_filter_bitmap ;

/* Variables and functions */
 int KDBG_TYPEFILTER_BITMAP_SIZE ; 
 int /*<<< orphan*/  _sysctl_enable_typefilter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_typefilter_all_reject() {
	uint8_t type_filter_bitmap[KDBG_TYPEFILTER_BITMAP_SIZE];
	memset(type_filter_bitmap, 0, sizeof(type_filter_bitmap));
	_sysctl_enable_typefilter(type_filter_bitmap);
}