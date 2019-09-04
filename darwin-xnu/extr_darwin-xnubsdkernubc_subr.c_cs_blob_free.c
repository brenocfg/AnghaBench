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
struct cs_blob {int /*<<< orphan*/ * csb_entitlements; scalar_t__ csb_mem_kaddr; int /*<<< orphan*/  csb_mem_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cs_blob* const,int) ; 
 int /*<<< orphan*/  osobject_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubc_cs_blob_deallocate (scalar_t__,int /*<<< orphan*/ ) ; 

void
cs_blob_free(
    struct cs_blob * const blob)
{
    if (blob != NULL) {
        if (blob->csb_mem_kaddr) {
            ubc_cs_blob_deallocate(blob->csb_mem_kaddr, blob->csb_mem_size);
            blob->csb_mem_kaddr = 0;
        }
        if (blob->csb_entitlements != NULL) {
            osobject_release(blob->csb_entitlements);
            blob->csb_entitlements = NULL;
        }
        kfree(blob, sizeof (*blob));
    }
}