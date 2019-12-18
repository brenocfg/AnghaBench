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
typedef  int /*<<< orphan*/  macro_lookup_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

char *
macro_expand_once (const char *source,
                   macro_lookup_ftype *lookup_func,
                   void *lookup_func_baton)
{
  error ("Expand-once not implemented yet.");
}