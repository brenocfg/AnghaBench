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
struct cs_blob {void* csb_entitlements; } ;

/* Variables and functions */
 int /*<<< orphan*/  osobject_retain (void*) ; 

void *
csblob_entitlements_dictionary_copy(struct cs_blob *csblob)
{
    if (!csblob->csb_entitlements) return NULL;
    osobject_retain(csblob->csb_entitlements);
    return csblob->csb_entitlements;
}