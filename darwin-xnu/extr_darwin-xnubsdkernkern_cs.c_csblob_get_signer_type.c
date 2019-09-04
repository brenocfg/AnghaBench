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
struct cs_blob {unsigned int csb_signer_type; } ;

/* Variables and functions */

unsigned int
csblob_get_signer_type(struct cs_blob *csblob)
{
	return csblob->csb_signer_type;
}