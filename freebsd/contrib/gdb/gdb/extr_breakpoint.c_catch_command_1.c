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

/* Variables and functions */
 int /*<<< orphan*/  EX_EVENT_CATCH ; 
 int /*<<< orphan*/  EX_EVENT_THROW ; 
 int /*<<< orphan*/  catch_exception_command_1 (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  catch_exec_command_1 (char*,int,int) ; 
 int /*<<< orphan*/  catch_fork ; 
 int /*<<< orphan*/  catch_fork_command_1 (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  catch_load_command_1 (char*,int,int) ; 
 int /*<<< orphan*/  catch_unload_command_1 (char*,int,int) ; 
 int /*<<< orphan*/  catch_vfork ; 
 char* ep_find_event_name_end (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
catch_command_1 (char *arg, int tempflag, int from_tty)
{

  /* The first argument may be an event name, such as "start" or "load".
     If so, then handle it as such.  If it doesn't match an event name,
     then attempt to interpret it as an exception name.  (This latter is
     the v4.16-and-earlier GDB meaning of the "catch" command.)

     First, try to find the bounds of what might be an event name. */
  char *arg1_start = arg;
  char *arg1_end;
  int arg1_length;

  if (arg1_start == NULL)
    {
      /* Old behaviour was to use pre-v-4.16 syntax */
      /* catch_throw_command_1 (arg1_start, tempflag, from_tty); */
      /* return; */
      /* Now, this is not allowed */
      error ("Catch requires an event name.");

    }
  arg1_end = ep_find_event_name_end (arg1_start);
  if (arg1_end == NULL)
    error ("catch requires an event");
  arg1_length = arg1_end + 1 - arg1_start;

  /* Try to match what we found against known event names. */
  if (strncmp (arg1_start, "signal", arg1_length) == 0)
    {
      error ("Catch of signal not yet implemented");
    }
  else if (strncmp (arg1_start, "catch", arg1_length) == 0)
    {
      catch_exception_command_1 (EX_EVENT_CATCH, arg1_end + 1, 
				 tempflag, from_tty);
    }
  else if (strncmp (arg1_start, "throw", arg1_length) == 0)
    {
      catch_exception_command_1 (EX_EVENT_THROW, arg1_end + 1, 
				 tempflag, from_tty);
    }
  else if (strncmp (arg1_start, "thread_start", arg1_length) == 0)
    {
      error ("Catch of thread_start not yet implemented");
    }
  else if (strncmp (arg1_start, "thread_exit", arg1_length) == 0)
    {
      error ("Catch of thread_exit not yet implemented");
    }
  else if (strncmp (arg1_start, "thread_join", arg1_length) == 0)
    {
      error ("Catch of thread_join not yet implemented");
    }
  else if (strncmp (arg1_start, "start", arg1_length) == 0)
    {
      error ("Catch of start not yet implemented");
    }
  else if (strncmp (arg1_start, "exit", arg1_length) == 0)
    {
      error ("Catch of exit not yet implemented");
    }
  else if (strncmp (arg1_start, "fork", arg1_length) == 0)
    {
      catch_fork_command_1 (catch_fork, arg1_end + 1, tempflag, from_tty);
    }
  else if (strncmp (arg1_start, "vfork", arg1_length) == 0)
    {
      catch_fork_command_1 (catch_vfork, arg1_end + 1, tempflag, from_tty);
    }
  else if (strncmp (arg1_start, "exec", arg1_length) == 0)
    {
      catch_exec_command_1 (arg1_end + 1, tempflag, from_tty);
    }
  else if (strncmp (arg1_start, "load", arg1_length) == 0)
    {
      catch_load_command_1 (arg1_end + 1, tempflag, from_tty);
    }
  else if (strncmp (arg1_start, "unload", arg1_length) == 0)
    {
      catch_unload_command_1 (arg1_end + 1, tempflag, from_tty);
    }
  else if (strncmp (arg1_start, "stop", arg1_length) == 0)
    {
      error ("Catch of stop not yet implemented");
    }

  /* This doesn't appear to be an event name */

  else
    {
      /* Pre-v.4.16 behaviour was to treat the argument
         as the name of an exception */
      /* catch_throw_command_1 (arg1_start, tempflag, from_tty); */
      /* Now this is not allowed */
      error ("Unknown event kind specified for catch");

    }
}