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

/* Variables and functions */
 int /*<<< orphan*/ * h_live ; 
 int /*<<< orphan*/ * h_queue ; 
 int /*<<< orphan*/ * h_scan ; 
 int /*<<< orphan*/  hb_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_global_close () ; 

void
ghb_backend_close()
{
    if (h_live != NULL)
        hb_close(&h_live);
    if (h_queue != NULL)
        hb_close(&h_queue);
    if (h_scan != NULL)
        hb_close(&h_scan);
    hb_global_close();
}