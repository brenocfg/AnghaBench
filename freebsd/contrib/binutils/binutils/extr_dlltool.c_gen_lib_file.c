#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ private; int /*<<< orphan*/  next; int /*<<< orphan*/  forward; int /*<<< orphan*/  hint; int /*<<< orphan*/  data; int /*<<< orphan*/  noname; int /*<<< orphan*/  constant; int /*<<< orphan*/  ordinal; int /*<<< orphan*/  name; int /*<<< orphan*/  import_name; int /*<<< orphan*/  internal_name; } ;
typedef  TYPE_1__ export_type ;
struct TYPE_14__ {int has_armap; struct TYPE_14__* archive_next; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  HOW_BFD_WRITE_TARGET ; 
 int PREFIX_ALIAS_BASE ; 
 char* TMP_HEAD_O ; 
 char* TMP_HEAD_S ; 
 char* TMP_STUB ; 
 char* TMP_TAIL_O ; 
 char* TMP_TAIL_S ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ alloca (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bfd_archive ; 
 int /*<<< orphan*/  bfd_close (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 TYPE_2__* bfd_openw (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_archive_head (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_set_format (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__** d_exports_lexically ; 
 int dontdeltemps ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ext_prefix_alias ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 char* imp_name ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,...) ; 
 TYPE_2__* make_head () ; 
 int /*<<< orphan*/  make_imp_label (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* make_one_lib_file (TYPE_1__*,int) ; 
 TYPE_2__* make_tail () ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void
gen_lib_file (void)
{
  int i;
  export_type *exp;
  bfd *ar_head;
  bfd *ar_tail;
  bfd *outarch;
  bfd * head  = 0;

  unlink (imp_name);

  outarch = bfd_openw (imp_name, HOW_BFD_WRITE_TARGET);

  if (!outarch)
    /* xgettext:c-format */
    fatal (_("Can't open .lib file: %s"), imp_name);

  /* xgettext:c-format */
  inform (_("Creating library file: %s"), imp_name);

  bfd_set_format (outarch, bfd_archive);
  outarch->has_armap = 1;

  /* Work out a reasonable size of things to put onto one line.  */
  ar_head = make_head ();
  ar_tail = make_tail();

  if (ar_head == NULL || ar_tail == NULL)
    return;

  for (i = 0; (exp = d_exports_lexically[i]); i++)
    {
      bfd *n;
      /* Don't add PRIVATE entries to import lib.  */
      if (exp->private)
	continue;
      n = make_one_lib_file (exp, i);
      n->archive_next = head;
      head = n;
      if (ext_prefix_alias)
	{
	  export_type alias_exp;

	  assert (i < PREFIX_ALIAS_BASE);
	  alias_exp.name = make_imp_label (ext_prefix_alias, exp->name);
	  alias_exp.internal_name = exp->internal_name;
	  alias_exp.import_name = exp->name;
	  alias_exp.ordinal = exp->ordinal;
	  alias_exp.constant = exp->constant;
	  alias_exp.noname = exp->noname;
	  alias_exp.private = exp->private;
	  alias_exp.data = exp->data;
	  alias_exp.hint = exp->hint;
	  alias_exp.forward = exp->forward;
	  alias_exp.next = exp->next;
	  n = make_one_lib_file (&alias_exp, i + PREFIX_ALIAS_BASE);
	  n->archive_next = head;
	  head = n;
	}
    }

  /* Now stick them all into the archive.  */
  ar_head->archive_next = head;
  ar_tail->archive_next = ar_head;
  head = ar_tail;

  if (! bfd_set_archive_head (outarch, head))
    bfd_fatal ("bfd_set_archive_head");

  if (! bfd_close (outarch))
    bfd_fatal (imp_name);

  while (head != NULL)
    {
      bfd *n = head->archive_next;
      bfd_close (head);
      head = n;
    }

  /* Delete all the temp files.  */
  if (dontdeltemps == 0)
    {
      unlink (TMP_HEAD_O);
      unlink (TMP_HEAD_S);
      unlink (TMP_TAIL_O);
      unlink (TMP_TAIL_S);
    }

  if (dontdeltemps < 2)
    {
      char *name;

      name = (char *) alloca (strlen (TMP_STUB) + 10);
      for (i = 0; (exp = d_exports_lexically[i]); i++)
	{
	  /* Don't delete non-existent stubs for PRIVATE entries.  */
          if (exp->private)
	    continue;
	  sprintf (name, "%s%05d.o", TMP_STUB, i);
	  if (unlink (name) < 0)
	    /* xgettext:c-format */
	    non_fatal (_("cannot delete %s: %s"), name, strerror (errno));
	  if (ext_prefix_alias)
	    {
	      sprintf (name, "%s%05d.o", TMP_STUB, i + PREFIX_ALIAS_BASE);
	      if (unlink (name) < 0)
		/* xgettext:c-format */
		non_fatal (_("cannot delete %s: %s"), name, strerror (errno));
	    }
	}
    }

  inform (_("Created lib file"));
}