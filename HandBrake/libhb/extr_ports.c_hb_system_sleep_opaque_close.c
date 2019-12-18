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
typedef  int /*<<< orphan*/  IOPMAssertionID ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_system_sleep_private_enable (void*) ; 

void hb_system_sleep_opaque_close(void **opaque)
{
    if (*opaque != NULL)
    {
        hb_system_sleep_private_enable(*opaque);
    }
#ifdef __APPLE__
    if (*opaque != NULL)
    {
        IOPMAssertionID *assertionID = (IOPMAssertionID*)*opaque;
        free(assertionID);
    }
#endif
    *opaque = NULL;
}