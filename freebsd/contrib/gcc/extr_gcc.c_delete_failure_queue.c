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
struct temp_file {int /*<<< orphan*/  name; struct temp_file* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_if_ordinary (int /*<<< orphan*/ ) ; 
 struct temp_file* failure_delete_queue ; 

__attribute__((used)) static void
delete_failure_queue (void)
{
  struct temp_file *temp;

  for (temp = failure_delete_queue; temp; temp = temp->next)
    delete_if_ordinary (temp->name);
}