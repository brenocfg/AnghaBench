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
struct ptr_info_def {int /*<<< orphan*/  pt_vars; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
ptr_info_hash (const void *p)
{
  const struct ptr_info_def *n = (const struct ptr_info_def *) p;
  return bitmap_hash (n->pt_vars);
}