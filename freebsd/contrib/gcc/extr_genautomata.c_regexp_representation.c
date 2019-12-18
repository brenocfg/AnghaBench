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
typedef  int /*<<< orphan*/  regexp_t ;

/* Variables and functions */
 int /*<<< orphan*/  form_regexp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irp ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,char) ; 
 char const* obstack_base (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
regexp_representation (regexp_t regexp)
{
  form_regexp (regexp);
  obstack_1grow (&irp, '\0');
  return obstack_base (&irp);
}