#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fd; int /*<<< orphan*/  proc; } ;
typedef  TYPE_1__ gdb_event ;

/* Variables and functions */
 int /*<<< orphan*/  handle_file_event ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static gdb_event *
create_file_event (int fd)
{
  gdb_event *file_event_ptr;

  file_event_ptr = (gdb_event *) xmalloc (sizeof (gdb_event));
  file_event_ptr->proc = handle_file_event;
  file_event_ptr->fd = fd;
  return (file_event_ptr);
}