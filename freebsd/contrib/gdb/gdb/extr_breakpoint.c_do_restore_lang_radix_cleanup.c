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
struct lang_and_radix {int /*<<< orphan*/  radix; int /*<<< orphan*/  lang; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_radix ; 
 int /*<<< orphan*/  set_language (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_restore_lang_radix_cleanup (void *old)
{
  struct lang_and_radix *p = old;
  set_language (p->lang);
  input_radix = p->radix;
}