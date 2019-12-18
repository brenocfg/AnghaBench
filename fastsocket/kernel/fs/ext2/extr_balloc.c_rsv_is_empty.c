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
struct ext2_reserve_window {scalar_t__ _rsv_end; } ;

/* Variables and functions */
 scalar_t__ EXT2_RESERVE_WINDOW_NOT_ALLOCATED ; 

__attribute__((used)) static inline int rsv_is_empty(struct ext2_reserve_window *rsv)
{
	/* a valid reservation end block could not be 0 */
	return (rsv->_rsv_end == EXT2_RESERVE_WINDOW_NOT_ALLOCATED);
}