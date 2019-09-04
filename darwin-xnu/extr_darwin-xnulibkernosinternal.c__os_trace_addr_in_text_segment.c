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
struct mach_header {int magic; } ;

/* Variables and functions */
#define  MH_MAGIC 129 
#define  MH_MAGIC_64 128 
 int _os_trace_addr_in_text_segment_32 (void const*,void const*) ; 
 int _os_trace_addr_in_text_segment_64 (void const*,void const*) ; 

bool
_os_trace_addr_in_text_segment(const void *dso, const void *addr)
{
    const struct mach_header *mhp = (const struct mach_header *) dso;
    bool retval = false;

    switch (mhp->magic) {
        case MH_MAGIC:
            retval = _os_trace_addr_in_text_segment_32(dso, addr);
            break;

        case MH_MAGIC_64:
            retval = _os_trace_addr_in_text_segment_64(dso, addr);
            break;

        default:
            retval = false;
            break;
    }

    return retval;
}