#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 TYPE_1__ ggenie ; 
 int /*<<< orphan*/  ggenie_switch (int /*<<< orphan*/ ) ; 

void ggenie_shutdown(void)
{
  if (ggenie.enabled)
  {
    ggenie_switch(0);
    ggenie.enabled = 0;
  }
}