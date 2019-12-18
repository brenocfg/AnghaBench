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
struct cs_blob {scalar_t__ csb_platform_binary; } ;

/* Variables and functions */

int
csblob_get_platform_binary(struct cs_blob *blob)
{
    if (blob && blob->csb_platform_binary)
	return 1;
    return 0;
}