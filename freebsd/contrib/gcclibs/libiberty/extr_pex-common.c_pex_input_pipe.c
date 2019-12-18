#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pex_obj {scalar_t__ count; int flags; int next_input; TYPE_1__* funcs; scalar_t__ next_input_name; } ;
struct TYPE_2__ {scalar_t__ (* pipe ) (struct pex_obj*,int*,int) ;int /*<<< orphan*/  (* close ) (struct pex_obj*,int) ;int /*<<< orphan*/ * (* fdopenw ) (struct pex_obj*,int,int) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int PEX_USE_PIPES ; 
 size_t READ_PORT ; 
 int STDIN_FILE_NO ; 
 size_t WRITE_PORT ; 
 int errno ; 
 scalar_t__ stub1 (struct pex_obj*,int*,int) ; 
 int /*<<< orphan*/ * stub2 (struct pex_obj*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct pex_obj*,int) ; 
 int /*<<< orphan*/  stub4 (struct pex_obj*,int) ; 

FILE *
pex_input_pipe (struct pex_obj *obj, int binary)
{
  int p[2];
  FILE *f;

  /* You must call pex_input_pipe before the first pex_run or pex_one.  */
  if (obj->count > 0)
    goto usage_error;

  /* You must be using pipes.  Implementations that don't support
     pipes clear this flag before calling pex_init_common.  */
  if (! (obj->flags & PEX_USE_PIPES))
    goto usage_error;

  /* If we have somehow already selected other input, that's a
     mistake.  */
  if ((obj->next_input >= 0 && obj->next_input != STDIN_FILE_NO)
      || obj->next_input_name)
    goto usage_error;

  if (obj->funcs->pipe (obj, p, binary != 0) < 0)
    return NULL;

  f = obj->funcs->fdopenw (obj, p[WRITE_PORT], binary != 0);
  if (! f)
    {
      int saved_errno = errno;
      obj->funcs->close (obj, p[READ_PORT]);
      obj->funcs->close (obj, p[WRITE_PORT]);
      errno = saved_errno;
      return NULL;
    }

  obj->next_input = p[READ_PORT];

  return f;

 usage_error:
  errno = EINVAL;
  return NULL;
}