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
struct cs_blob {int /*<<< orphan*/ * csb_entitlements; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osobject_retain (void*) ; 

void
csblob_entitlements_dictionary_set(struct cs_blob *csblob, void * entitlements)
{
    assert(csblob->csb_entitlements == NULL);
    if (entitlements) osobject_retain(entitlements);
    csblob->csb_entitlements = entitlements;
}