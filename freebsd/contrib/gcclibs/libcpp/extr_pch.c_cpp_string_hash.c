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
struct cpp_string {int /*<<< orphan*/  len; int /*<<< orphan*/  text; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  hashmem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
cpp_string_hash (const void *a_p)
{
  const struct cpp_string *a = (const struct cpp_string *) a_p;
  return hashmem (a->text, a->len);
}