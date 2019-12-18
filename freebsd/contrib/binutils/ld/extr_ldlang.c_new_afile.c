#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lang_statement_union_type ;
struct TYPE_7__ {int /*<<< orphan*/ * next; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {char const* target; char const* filename; char const* local_sym_name; int /*<<< orphan*/ * next_real_file; void* loaded; int /*<<< orphan*/  whole_archive; int /*<<< orphan*/  as_needed; int /*<<< orphan*/  add_needed; int /*<<< orphan*/  dynamic; scalar_t__ symbol_count; int /*<<< orphan*/ * next; int /*<<< orphan*/ * asymbols; int /*<<< orphan*/ * the_bfd; void* search_dirs_flag; void* just_syms_flag; void* real; void* is_archive; void* sysrooted; TYPE_1__ header; } ;
typedef  TYPE_2__ lang_input_statement_type ;
typedef  int lang_input_file_enum_type ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_9__ {int /*<<< orphan*/  dynamic_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL () ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  add_needed ; 
 int /*<<< orphan*/  as_needed ; 
 char const* concat (char*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_6__ config ; 
 int /*<<< orphan*/  input_file_chain ; 
 void* lang_has_input_file ; 
#define  lang_input_file_is_fake_enum 133 
#define  lang_input_file_is_file_enum 132 
#define  lang_input_file_is_l_enum 131 
#define  lang_input_file_is_marker_enum 130 
#define  lang_input_file_is_search_file_enum 129 
#define  lang_input_file_is_symbols_only_enum 128 
 int /*<<< orphan*/  lang_input_statement ; 
 int /*<<< orphan*/  lang_input_statement_enum ; 
 int /*<<< orphan*/  lang_statement_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 void* ldlang_sysrooted_script ; 
 TYPE_2__* new_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* stat_alloc (int) ; 
 int /*<<< orphan*/  stat_ptr ; 
 int /*<<< orphan*/  whole_archive ; 

__attribute__((used)) static lang_input_statement_type *
new_afile (const char *name,
	   lang_input_file_enum_type file_type,
	   const char *target,
	   bfd_boolean add_to_list)
{
  lang_input_statement_type *p;

  if (add_to_list)
    p = new_stat (lang_input_statement, stat_ptr);
  else
    {
      p = stat_alloc (sizeof (lang_input_statement_type));
      p->header.type = lang_input_statement_enum;
      p->header.next = NULL;
    }

  lang_has_input_file = TRUE;
  p->target = target;
  p->sysrooted = FALSE;

  if (file_type == lang_input_file_is_l_enum
      && name[0] == ':' && name[1] != '\0')
    {
      file_type = lang_input_file_is_search_file_enum;
      name = name + 1;
    }

  switch (file_type)
    {
    case lang_input_file_is_symbols_only_enum:
      p->filename = name;
      p->is_archive = FALSE;
      p->real = TRUE;
      p->local_sym_name = name;
      p->just_syms_flag = TRUE;
      p->search_dirs_flag = FALSE;
      break;
    case lang_input_file_is_fake_enum:
      p->filename = name;
      p->is_archive = FALSE;
      p->real = FALSE;
      p->local_sym_name = name;
      p->just_syms_flag = FALSE;
      p->search_dirs_flag = FALSE;
      break;
    case lang_input_file_is_l_enum:
      p->is_archive = TRUE;
      p->filename = name;
      p->real = TRUE;
      p->local_sym_name = concat ("-l", name, NULL);
      p->just_syms_flag = FALSE;
      p->search_dirs_flag = TRUE;
      break;
    case lang_input_file_is_marker_enum:
      p->filename = name;
      p->is_archive = FALSE;
      p->real = FALSE;
      p->local_sym_name = name;
      p->just_syms_flag = FALSE;
      p->search_dirs_flag = TRUE;
      break;
    case lang_input_file_is_search_file_enum:
      p->sysrooted = ldlang_sysrooted_script;
      p->filename = name;
      p->is_archive = FALSE;
      p->real = TRUE;
      p->local_sym_name = name;
      p->just_syms_flag = FALSE;
      p->search_dirs_flag = TRUE;
      break;
    case lang_input_file_is_file_enum:
      p->filename = name;
      p->is_archive = FALSE;
      p->real = TRUE;
      p->local_sym_name = name;
      p->just_syms_flag = FALSE;
      p->search_dirs_flag = FALSE;
      break;
    default:
      FAIL ();
    }
  p->the_bfd = NULL;
  p->asymbols = NULL;
  p->next_real_file = NULL;
  p->next = NULL;
  p->symbol_count = 0;
  p->dynamic = config.dynamic_link;
  p->add_needed = add_needed;
  p->as_needed = as_needed;
  p->whole_archive = whole_archive;
  p->loaded = FALSE;
  lang_statement_append (&input_file_chain,
			 (lang_statement_union_type *) p,
			 &p->next_real_file);
  return p;
}