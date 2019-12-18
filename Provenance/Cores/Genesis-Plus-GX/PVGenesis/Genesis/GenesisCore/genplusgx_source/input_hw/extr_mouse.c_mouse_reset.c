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
struct TYPE_4__ {scalar_t__** analog; } ;
struct TYPE_3__ {int State; int Port; scalar_t__ Wait; scalar_t__ Counter; } ;

/* Variables and functions */
 TYPE_2__ input ; 
 TYPE_1__ mouse ; 

void mouse_reset(int port)
{
  input.analog[port][0] = 0;
  input.analog[port][1] = 0;
  mouse.State = 0x60;
  mouse.Counter = 0;
  mouse.Wait = 0;
  mouse.Port = port;
}