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
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static void
basic_type_complaint (int arg1, const char *arg2)
{
  complaint (&symfile_complaints, "cannot map ECOFF basic type 0x%x for %s",
	     arg1, arg2);
}