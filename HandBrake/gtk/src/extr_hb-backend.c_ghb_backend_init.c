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
typedef  int /*<<< orphan*/  gint ;

/* Variables and functions */
 void* h_live ; 
 void* h_queue ; 
 void* h_scan ; 
 int /*<<< orphan*/  hb_global_init () ; 
 void* hb_init (int /*<<< orphan*/ ) ; 

void
ghb_backend_init(gint debug)
{
    /* Init libhb */
    hb_global_init();
    h_scan = hb_init( debug );
    h_queue = hb_init( debug );
    h_live = hb_init( debug );
}