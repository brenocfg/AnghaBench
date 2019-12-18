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
typedef  int process_state_t ;

/* Variables and functions */
#define  FAKE_STEPPING 132 
#define  FORKING 131 
#define  RUNNING 130 
#define  STOPPED 129 
#define  VFORKING 128 

__attribute__((used)) static char *
get_printable_name_of_process_state (process_state_t process_state)
{
  switch (process_state)
    {
    case STOPPED:
      return "STOPPED";
    case FAKE_STEPPING:
      return "FAKE_STEPPING";
    case RUNNING:
      return "RUNNING";
    case FORKING:
      return "FORKING";
    case VFORKING:
      return "VFORKING";
    default:
      return "?some unknown state?";
    }
}