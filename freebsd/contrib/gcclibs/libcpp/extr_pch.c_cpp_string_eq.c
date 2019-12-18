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
struct cpp_string {scalar_t__ len; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
cpp_string_eq (const void *a_p, const void *b_p)
{
  const struct cpp_string *a = (const struct cpp_string *) a_p;
  const struct cpp_string *b = (const struct cpp_string *) b_p;
  return (a->len == b->len
	  && memcmp (a->text, b->text, a->len) == 0);
}