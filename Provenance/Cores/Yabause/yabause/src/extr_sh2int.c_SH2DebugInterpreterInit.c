#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int breakpointEnabled; int backtraceEnabled; } ;
struct TYPE_3__ {int breakpointEnabled; int backtraceEnabled; } ;

/* Variables and functions */
 TYPE_2__* MSH2 ; 
 int /*<<< orphan*/  SH2InterpreterInit () ; 
 TYPE_1__* SSH2 ; 

int SH2DebugInterpreterInit() {

  SH2InterpreterInit();
  MSH2->breakpointEnabled = 1;
  SSH2->breakpointEnabled = 1;  
  MSH2->backtraceEnabled = 1;
  SSH2->backtraceEnabled = 1;
  return 0;
}