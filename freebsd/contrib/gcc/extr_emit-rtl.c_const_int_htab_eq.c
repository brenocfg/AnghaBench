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
typedef  int /*<<< orphan*/  rtx ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ const INTVAL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
const_int_htab_eq (const void *x, const void *y)
{
  return (INTVAL ((rtx) x) == *((const HOST_WIDE_INT *) y));
}