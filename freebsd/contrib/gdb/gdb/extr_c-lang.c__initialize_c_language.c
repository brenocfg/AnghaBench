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
 int /*<<< orphan*/  add_language (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asm_language_defn ; 
 int /*<<< orphan*/  c_language_defn ; 
 int /*<<< orphan*/  cplus_language_defn ; 
 int /*<<< orphan*/  minimal_language_defn ; 

void
_initialize_c_language (void)
{
  add_language (&c_language_defn);
  add_language (&cplus_language_defn);
  add_language (&asm_language_defn);
  add_language (&minimal_language_defn);
}