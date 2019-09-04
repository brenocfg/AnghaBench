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
struct cs_blob {int /*<<< orphan*/  const* csb_cdhash; } ;

/* Variables and functions */

const uint8_t *
csblob_get_cdhash(struct cs_blob *csblob)
{
	return csblob->csb_cdhash;
}