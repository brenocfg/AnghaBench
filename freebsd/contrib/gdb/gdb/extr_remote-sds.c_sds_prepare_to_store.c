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

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_BYTES ; 
 int /*<<< orphan*/  deprecated_read_register_bytes (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sds_prepare_to_store (void)
{
  /* Make sure the entire registers array is valid.  */
  deprecated_read_register_bytes (0, (char *) NULL, DEPRECATED_REGISTER_BYTES);
}