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
struct _Unwind_Context {int dummy; } ;
typedef  int /*<<< orphan*/  _Unwind_FrameState ;

/* Variables and functions */
 int /*<<< orphan*/  uw_update_context (struct _Unwind_Context*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uw_advance_context (struct _Unwind_Context *context, _Unwind_FrameState *fs)
{
  uw_update_context (context, fs);
}