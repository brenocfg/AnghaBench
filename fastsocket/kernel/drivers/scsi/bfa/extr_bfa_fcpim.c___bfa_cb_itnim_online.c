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
struct bfa_itnim_s {int /*<<< orphan*/  ditn; } ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_cb_itnim_online (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__bfa_cb_itnim_online(void *cbarg, bfa_boolean_t complete)
{
	struct bfa_itnim_s *itnim = cbarg;

	if (complete)
		bfa_cb_itnim_online(itnim->ditn);
}