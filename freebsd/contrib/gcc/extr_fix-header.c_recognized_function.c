#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct partial_proto {unsigned int line_seen; struct partial_proto* next; struct fn_decl* fn; } ;
struct fn_decl {char* params; char* fname; struct partial_proto* partial; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct TYPE_5__ {TYPE_1__ val; } ;
typedef  TYPE_2__ cpp_token ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ NODE_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ REQUIRED (struct fn_decl*) ; 
 int /*<<< orphan*/  SET_SEEN (struct fn_decl*) ; 
 int cur_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* inc_filename ; 
 int inc_filename_length ; 
 struct fn_decl* lookup_std_proto (char const*,int /*<<< orphan*/ ) ; 
 struct partial_proto* obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  partial_count ; 
 struct partial_proto* partial_proto_list ; 
 int /*<<< orphan*/  required_unseen_count ; 
 int /*<<< orphan*/  scan_file_obstack ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int) ; 
 int strlen (int) ; 
 scalar_t__ verbose ; 

void
recognized_function (const cpp_token *fname, unsigned int line, int kind,
		     int have_arg_list)
{
  struct partial_proto *partial;
  int i;
  struct fn_decl *fn;

  fn = lookup_std_proto ((const char *) NODE_NAME (fname->val.node),
			 NODE_LEN (fname->val.node));

  /* Remove the function from the list of required function.  */
  if (fn)
    {
      if (REQUIRED (fn))
	required_unseen_count--;
      SET_SEEN (fn);
    }

  /* If we have a full prototype, we're done.  */
  if (have_arg_list)
    return;

  if (kind == 'I')  /* don't edit inline function */
    return;

  /* If the partial prototype was included from some other file,
     we don't need to patch it up (in this run).  */
  i = strlen (cur_file);
  if (i < inc_filename_length
      || strcmp (inc_filename, cur_file + (i - inc_filename_length)) != 0)
    return;

  if (fn == NULL)
    return;
  if (fn->params[0] == '\0')
    return;

  /* We only have a partial function declaration,
     so remember that we have to add a complete prototype.  */
  partial_count++;
  partial = obstack_alloc (&scan_file_obstack, sizeof (struct partial_proto));
  partial->line_seen = line;
  partial->fn = fn;
  fn->partial = partial;
  partial->next = partial_proto_list;
  partial_proto_list = partial;
  if (verbose)
    {
      fprintf (stderr, "(%s: %s non-prototype function declaration.)\n",
	       inc_filename, fn->fname);
    }
}