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
struct spec_function {char* (* func ) (int,char const**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_args () ; 
 int arg_going ; 
 char const** argbuf ; 
 int argbuf_index ; 
 int argbuf_length ; 
 int delete_this_arg ; 
 scalar_t__ do_spec_2 (char const*) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  free (char const**) ; 
 int input_from_pipe ; 
 struct spec_function* lookup_spec_function (char const*) ; 
 char* stub1 (int,char const**) ; 
 char const* suffix_subst ; 
 int this_is_library_file ; 
 int this_is_output_file ; 

__attribute__((used)) static const char *
eval_spec_function (const char *func, const char *args)
{
  const struct spec_function *sf;
  const char *funcval;

  /* Saved spec processing context.  */
  int save_argbuf_index;
  int save_argbuf_length;
  const char **save_argbuf;

  int save_arg_going;
  int save_delete_this_arg;
  int save_this_is_output_file;
  int save_this_is_library_file;
  int save_input_from_pipe;
  const char *save_suffix_subst;


  sf = lookup_spec_function (func);
  if (sf == NULL)
    fatal ("unknown spec function '%s'", func);

  /* Push the spec processing context.  */
  save_argbuf_index = argbuf_index;
  save_argbuf_length = argbuf_length;
  save_argbuf = argbuf;

  save_arg_going = arg_going;
  save_delete_this_arg = delete_this_arg;
  save_this_is_output_file = this_is_output_file;
  save_this_is_library_file = this_is_library_file;
  save_input_from_pipe = input_from_pipe;
  save_suffix_subst = suffix_subst;

  /* Create a new spec processing context, and build the function
     arguments.  */

  alloc_args ();
  if (do_spec_2 (args) < 0)
    fatal ("error in args to spec function '%s'", func);

  /* argbuf_index is an index for the next argument to be inserted, and
     so contains the count of the args already inserted.  */

  funcval = (*sf->func) (argbuf_index, argbuf);

  /* Pop the spec processing context.  */
  argbuf_index = save_argbuf_index;
  argbuf_length = save_argbuf_length;
  free (argbuf);
  argbuf = save_argbuf;

  arg_going = save_arg_going;
  delete_this_arg = save_delete_this_arg;
  this_is_output_file = save_this_is_output_file;
  this_is_library_file = save_this_is_library_file;
  input_from_pipe = save_input_from_pipe;
  suffix_subst = save_suffix_subst;

  return funcval;
}