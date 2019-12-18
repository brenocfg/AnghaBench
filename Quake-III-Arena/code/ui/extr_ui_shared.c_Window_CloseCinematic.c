#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ style; int cinematic; } ;
typedef  TYPE_1__ windowDef_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* stopCinematic ) (int) ;} ;

/* Variables and functions */
 TYPE_3__* DC ; 
 scalar_t__ WINDOW_STYLE_CINEMATIC ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void Window_CloseCinematic(windowDef_t *window) {
	if (window->style == WINDOW_STYLE_CINEMATIC && window->cinematic >= 0) {
		DC->stopCinematic(window->cinematic);
		window->cinematic = -1;
	}
}