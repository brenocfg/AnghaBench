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
struct inferior_status {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_restore_inferior_status_cleanup ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct inferior_status*) ; 

struct cleanup *
make_cleanup_restore_inferior_status (struct inferior_status *inf_status)
{
  return make_cleanup (do_restore_inferior_status_cleanup, inf_status);
}