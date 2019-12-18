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
typedef  int /*<<< orphan*/  _Unwind_Control_Block ;
typedef  int /*<<< orphan*/  _Unwind_Context ;

/* Variables and functions */
 int /*<<< orphan*/  R_IP ; 
 scalar_t__ _Unwind_GetGR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline _Unwind_Control_Block *
unwind_UCB_from_context (_Unwind_Context * context)
{
  return (_Unwind_Control_Block *) _Unwind_GetGR (context, R_IP);
}