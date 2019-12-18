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
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ pending_invalid_xref ; 
 int /*<<< orphan*/  pending_invalid_xref_location ; 

void
pending_xref_error (void)
{
  if (pending_invalid_xref != 0)
    error ("%H%qE defined as wrong kind of tag",
	   &pending_invalid_xref_location, pending_invalid_xref);
  pending_invalid_xref = 0;
}