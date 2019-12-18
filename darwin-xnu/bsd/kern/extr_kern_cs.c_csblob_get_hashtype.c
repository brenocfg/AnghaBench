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
typedef  int /*<<< orphan*/  uint8_t ;
struct cs_blob {int /*<<< orphan*/ * csb_hashtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_hash_type (int /*<<< orphan*/ *) ; 

uint8_t
csblob_get_hashtype(struct cs_blob const * const blob)
{
    return blob->csb_hashtype != NULL ? cs_hash_type(blob->csb_hashtype) : 0;
}