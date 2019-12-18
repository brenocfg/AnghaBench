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
struct TYPE_2__ {scalar_t__ display; } ;

/* Variables and functions */
 TYPE_1__ g_xstuff ; 
 int /*<<< orphan*/  x11h_update (int (*) (void*,int,int),int (*) (void*,int,int,int,int),int (*) (void*,int,int),void*) ; 

int xenv_update(int (*key_cb)(void *cb_arg, int kc, int is_pressed),
		int (*mouseb_cb)(void *cb_arg, int x, int y, int button, int is_pressed),
		int (*mousem_cb)(void *cb_arg, int x, int y),
		void *cb_arg)
{
	if (g_xstuff.display) {
		x11h_update(key_cb, mouseb_cb, mousem_cb, cb_arg);
		return 0;
	}

	// TODO: read tty?
	return -1;
}