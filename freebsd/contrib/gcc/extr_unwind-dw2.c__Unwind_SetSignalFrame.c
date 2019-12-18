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
struct _Unwind_Context {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGNAL_FRAME_BIT ; 

__attribute__((used)) static inline void
_Unwind_SetSignalFrame (struct _Unwind_Context *context, int val)
{
  if (val)
    context->flags |= SIGNAL_FRAME_BIT;
  else
    context->flags &= ~SIGNAL_FRAME_BIT;
}