#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ window; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ xmap; } ;
typedef  TYPE_2__ XEvent ;
typedef  int /*<<< orphan*/  Display ;
typedef  int Bool ;

/* Variables and functions */
 scalar_t__ MapNotify ; 
 scalar_t__ g_x11_win ; 

__attribute__((used)) static Bool x11_wait_notify(Display *d, XEvent *e, char *arg)
{
   return e->type == MapNotify && e->xmap.window == g_x11_win;
}