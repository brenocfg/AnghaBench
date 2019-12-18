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
struct ilo_hwinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_pending_db (struct ilo_hwinfo*,int) ; 

__attribute__((used)) static inline void clear_device(struct ilo_hwinfo *hw)
{
	/* clear the device (reset bits, pending channel entries) */
	clear_pending_db(hw, -1);
}