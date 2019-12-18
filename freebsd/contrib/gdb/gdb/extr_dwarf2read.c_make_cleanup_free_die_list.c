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
struct die_info {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_free_die_list_cleanup ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct die_info*) ; 

__attribute__((used)) static struct cleanup *
make_cleanup_free_die_list (struct die_info *dies)
{
  return make_cleanup (do_free_die_list_cleanup, dies);
}