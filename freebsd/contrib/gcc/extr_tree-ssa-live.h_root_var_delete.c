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
typedef  int /*<<< orphan*/  root_var_p ;

/* Variables and functions */
 int /*<<< orphan*/  tpa_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
root_var_delete (root_var_p rv)
{
  tpa_delete (rv);
}