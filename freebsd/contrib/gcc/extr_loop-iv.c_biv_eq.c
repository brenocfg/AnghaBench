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
struct biv_entry {scalar_t__ regno; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
biv_eq (const void *b, const void *r)
{
  return ((const struct biv_entry *) b)->regno == REGNO ((rtx) r);
}