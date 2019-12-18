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
 int /*<<< orphan*/  begin_scope (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int check_specialization_scope () ; 
 int /*<<< orphan*/  note_template_header (int) ; 
 int /*<<< orphan*/  sk_template_spec ; 

bool
begin_specialization (void)
{
  begin_scope (sk_template_spec, NULL);
  note_template_header (1);
  return check_specialization_scope ();
}