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
struct ieee_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ieee_pop_type_used (struct ieee_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ieee_pop_unused_type (struct ieee_handle *info)
{
  (void) ieee_pop_type_used (info, FALSE);
}