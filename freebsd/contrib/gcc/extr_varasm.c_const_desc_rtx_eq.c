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
struct constant_descriptor_rtx {scalar_t__ mode; int /*<<< orphan*/  constant; } ;

/* Variables and functions */
 int rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
const_desc_rtx_eq (const void *a, const void *b)
{
  const struct constant_descriptor_rtx *x = a;
  const struct constant_descriptor_rtx *y = b;

  if (x->mode != y->mode)
    return 0;
  return rtx_equal_p (x->constant, y->constant);
}