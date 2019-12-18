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
struct vmballoon {int reset_required; } ;

/* Variables and functions */
#define  VMW_BALLOON_ERROR_RESET 129 
#define  VMW_BALLOON_SUCCESS 128 

__attribute__((used)) static bool vmballoon_check_status(struct vmballoon *b, unsigned long status)
{
	switch (status) {
	case VMW_BALLOON_SUCCESS:
		return true;

	case VMW_BALLOON_ERROR_RESET:
		b->reset_required = true;
		/* fall through */

	default:
		return false;
	}
}