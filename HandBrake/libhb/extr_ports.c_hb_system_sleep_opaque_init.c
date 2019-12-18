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
typedef  int IOPMAssertionID ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  hb_error (char*) ; 

void* hb_system_sleep_opaque_init()
{
    void *opaque = NULL;
#ifdef __APPLE__
    opaque = calloc(sizeof(IOPMAssertionID), 1);
    if (opaque == NULL)
    {
        hb_error("hb_system_sleep: failed to allocate opaque");
        return NULL;
    }

    IOPMAssertionID *assertionID = (IOPMAssertionID*)opaque;
    *assertionID = -1;
#endif
    return opaque;
}