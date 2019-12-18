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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  select_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_pc ; 

__attribute__((used)) static void
switch_to_thread (ptid_t ptid)
{
  if (ptid_equal (ptid, inferior_ptid))
    return;

  inferior_ptid = ptid;
  flush_cached_frames ();
  registers_changed ();
  stop_pc = read_pc ();
  select_frame (get_current_frame ());
}