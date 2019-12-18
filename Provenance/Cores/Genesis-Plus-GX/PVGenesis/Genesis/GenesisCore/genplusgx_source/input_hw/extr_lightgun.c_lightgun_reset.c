#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int w; int h; } ;
struct TYPE_8__ {TYPE_1__ viewport; } ;
struct TYPE_7__ {int** analog; } ;
struct TYPE_6__ {int State; int Port; } ;

/* Variables and functions */
 TYPE_4__ bitmap ; 
 TYPE_3__ input ; 
 TYPE_2__ lightgun ; 

void lightgun_reset(int port)
{
  input.analog[port][0] = bitmap.viewport.w / 2;
  input.analog[port][1] = bitmap.viewport.h / 2;
  lightgun.State = 0x40;
  lightgun.Port = 4;
}