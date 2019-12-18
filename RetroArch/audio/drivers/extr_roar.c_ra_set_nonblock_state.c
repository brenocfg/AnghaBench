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
struct TYPE_2__ {int nonblocking; int /*<<< orphan*/  vss; } ;
typedef  TYPE_1__ roar_t ;

/* Variables and functions */
 int /*<<< orphan*/  ROAR_VS_FALSE ; 
 int /*<<< orphan*/  ROAR_VS_TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ roar_vs_blocking (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void ra_set_nonblock_state(void *data, bool state)
{
   roar_t *roar = (roar_t*)data;
   if (roar_vs_blocking(roar->vss, (state) ? ROAR_VS_FALSE : ROAR_VS_TRUE, NULL) < 0)
      fprintf(stderr, "RetroArch [ERROR]: Can't set nonblocking. Will not be able to fast-forward.\n");
   roar->nonblocking = state;
}