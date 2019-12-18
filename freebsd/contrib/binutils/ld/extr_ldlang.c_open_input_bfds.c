#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_18__ ;
typedef  struct TYPE_23__   TYPE_17__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct bfd_link_hash_entry {int dummy; } ;
struct TYPE_33__ {int type; TYPE_10__* next; } ;
struct TYPE_21__ {void* loaded; int /*<<< orphan*/  the_bfd; int /*<<< orphan*/  whole_archive; int /*<<< orphan*/  target; int /*<<< orphan*/  real; } ;
struct TYPE_32__ {int /*<<< orphan*/  target; } ;
struct TYPE_30__ {TYPE_10__* head; } ;
struct TYPE_31__ {TYPE_6__ children; } ;
struct TYPE_27__ {TYPE_10__* head; } ;
struct TYPE_28__ {TYPE_3__ children; int /*<<< orphan*/  filename; } ;
struct TYPE_25__ {TYPE_10__* head; } ;
struct TYPE_26__ {TYPE_1__ children; } ;
struct TYPE_19__ {TYPE_9__ header; TYPE_13__ input_statement; TYPE_8__ target_statement; TYPE_7__ group_statement; TYPE_4__ wild_statement; TYPE_2__ output_section_statement; } ;
typedef  TYPE_10__ lang_statement_union_type ;
struct TYPE_20__ {TYPE_10__* head; TYPE_10__** tail; } ;
typedef  TYPE_11__ lang_statement_list_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_29__ {struct bfd_link_hash_entry* undefs_tail; } ;
struct TYPE_24__ {void* make_executable; } ;
struct TYPE_23__ {TYPE_10__* head; } ;
struct TYPE_22__ {TYPE_5__* hash; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_archive ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_18__ config ; 
 TYPE_17__ constructor_list ; 
 int /*<<< orphan*/  current_target ; 
#define  lang_constructors_statement_enum 133 
#define  lang_group_statement_enum 132 
#define  lang_input_statement_enum 131 
 int /*<<< orphan*/  lang_list_init (TYPE_11__*) ; 
#define  lang_output_section_statement_enum 130 
#define  lang_target_statement_enum 129 
#define  lang_wild_statement_enum 128 
 TYPE_15__ link_info ; 
 int /*<<< orphan*/  load_symbols (TYPE_13__*,TYPE_11__*) ; 
 int /*<<< orphan*/  lookup_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wildcardp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
open_input_bfds (lang_statement_union_type *s, bfd_boolean force)
{
  for (; s != NULL; s = s->header.next)
    {
      switch (s->header.type)
	{
	case lang_constructors_statement_enum:
	  open_input_bfds (constructor_list.head, force);
	  break;
	case lang_output_section_statement_enum:
	  open_input_bfds (s->output_section_statement.children.head, force);
	  break;
	case lang_wild_statement_enum:
	  /* Maybe we should load the file's symbols.  */
	  if (s->wild_statement.filename
	      && ! wildcardp (s->wild_statement.filename))
	    lookup_name (s->wild_statement.filename);
	  open_input_bfds (s->wild_statement.children.head, force);
	  break;
	case lang_group_statement_enum:
	  {
	    struct bfd_link_hash_entry *undefs;

	    /* We must continually search the entries in the group
	       until no new symbols are added to the list of undefined
	       symbols.  */

	    do
	      {
		undefs = link_info.hash->undefs_tail;
		open_input_bfds (s->group_statement.children.head, TRUE);
	      }
	    while (undefs != link_info.hash->undefs_tail);
	  }
	  break;
	case lang_target_statement_enum:
	  current_target = s->target_statement.target;
	  break;
	case lang_input_statement_enum:
	  if (s->input_statement.real)
	    {
	      lang_statement_list_type add;

	      s->input_statement.target = current_target;

	      /* If we are being called from within a group, and this
		 is an archive which has already been searched, then
		 force it to be researched unless the whole archive
		 has been loaded already.  */
	      if (force
		  && !s->input_statement.whole_archive
		  && s->input_statement.loaded
		  && bfd_check_format (s->input_statement.the_bfd,
				       bfd_archive))
		s->input_statement.loaded = FALSE;

	      lang_list_init (&add);

	      if (! load_symbols (&s->input_statement, &add))
		config.make_executable = FALSE;

	      if (add.head != NULL)
		{
		  *add.tail = s->header.next;
		  s->header.next = add.head;
		}
	    }
	  break;
	default:
	  break;
	}
    }
}