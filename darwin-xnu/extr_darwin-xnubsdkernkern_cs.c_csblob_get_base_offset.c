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
struct cs_blob {int /*<<< orphan*/  csb_base_offset; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */

off_t
csblob_get_base_offset(struct cs_blob *blob)
{
    return blob->csb_base_offset;
}