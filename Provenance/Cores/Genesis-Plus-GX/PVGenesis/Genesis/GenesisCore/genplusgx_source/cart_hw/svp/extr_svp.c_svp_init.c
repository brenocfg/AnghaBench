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
struct TYPE_2__ {scalar_t__ rom; } ;

/* Variables and functions */
 TYPE_1__ cart ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* svp ; 

void svp_init(void)
{
  svp = (void *) ((char *)cart.rom + 0x200000);
  memset(svp, 0, sizeof(*svp));
}