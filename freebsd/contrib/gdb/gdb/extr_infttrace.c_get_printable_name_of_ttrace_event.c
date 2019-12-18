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
typedef  int ttevents_t ;

/* Variables and functions */
#define  TTEVT_EXEC 140 
#define  TTEVT_EXIT 139 
#define  TTEVT_FORK 138 
#define  TTEVT_LWP_ABORT_SYSCALL 137 
#define  TTEVT_LWP_CREATE 136 
#define  TTEVT_LWP_EXIT 135 
#define  TTEVT_LWP_TERMINATE 134 
#define  TTEVT_NONE 133 
#define  TTEVT_SIGNAL 132 
#define  TTEVT_SYSCALL_ENTRY 131 
#define  TTEVT_SYSCALL_RESTART 130 
#define  TTEVT_SYSCALL_RETURN 129 
#define  TTEVT_VFORK 128 

char *
get_printable_name_of_ttrace_event (ttevents_t event)
{
  /* This enumeration is "gappy", so don't use a table. */
  switch (event)
    {

    case TTEVT_NONE:
      return "TTEVT_NONE";
    case TTEVT_SIGNAL:
      return "TTEVT_SIGNAL";
    case TTEVT_FORK:
      return "TTEVT_FORK";
    case TTEVT_EXEC:
      return "TTEVT_EXEC";
    case TTEVT_EXIT:
      return "TTEVT_EXIT";
    case TTEVT_VFORK:
      return "TTEVT_VFORK";
    case TTEVT_SYSCALL_RETURN:
      return "TTEVT_SYSCALL_RETURN";
    case TTEVT_LWP_CREATE:
      return "TTEVT_LWP_CREATE";
    case TTEVT_LWP_TERMINATE:
      return "TTEVT_LWP_TERMINATE";
    case TTEVT_LWP_EXIT:
      return "TTEVT_LWP_EXIT";
    case TTEVT_LWP_ABORT_SYSCALL:
      return "TTEVT_LWP_ABORT_SYSCALL";
    case TTEVT_SYSCALL_ENTRY:
      return "TTEVT_SYSCALL_ENTRY";
    case TTEVT_SYSCALL_RESTART:
      return "TTEVT_SYSCALL_RESTART";
    default:
      return "?new event?";
    }
}