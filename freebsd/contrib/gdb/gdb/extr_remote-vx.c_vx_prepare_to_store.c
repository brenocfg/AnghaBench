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
 int /*<<< orphan*/  deprecated_read_register_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vx_prepare_to_store (void)
{
  /* Fetch all registers, if any of them are not yet fetched.  */
  deprecated_read_register_bytes (0, NULL, DEPRECATED_REGISTER_BYTES);
}