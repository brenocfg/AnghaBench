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
struct dlm_ls {int /*<<< orphan*/  ls_uevent_wait; int /*<<< orphan*/  ls_flags; int /*<<< orphan*/  ls_uevent_result; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LSFL_UEVENT_WAIT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t dlm_event_store(struct dlm_ls *ls, const char *buf, size_t len)
{
	ls->ls_uevent_result = simple_strtol(buf, NULL, 0);
	set_bit(LSFL_UEVENT_WAIT, &ls->ls_flags);
	wake_up(&ls->ls_uevent_wait);
	return len;
}