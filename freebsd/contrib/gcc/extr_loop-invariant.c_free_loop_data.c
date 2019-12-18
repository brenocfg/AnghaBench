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
struct loop_data {int dummy; } ;
struct loop {int /*<<< orphan*/ * aux; } ;

/* Variables and functions */
 struct loop_data* LOOP_DATA (struct loop*) ; 
 int /*<<< orphan*/  free (struct loop_data*) ; 

__attribute__((used)) static void
free_loop_data (struct loop *loop)
{
  struct loop_data *data = LOOP_DATA (loop);

  free (data);
  loop->aux = NULL;
}