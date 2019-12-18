#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * the_bfd; } ;
typedef  TYPE_1__ lang_input_statement_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_link_add_symbols (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  einfo (char*,char const*) ; 
 TYPE_1__* lang_add_input_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_input_file_is_fake_enum ; 
 int /*<<< orphan*/  ldlang_add_file (TYPE_1__*) ; 

__attribute__((used)) static void
add_bfd_to_link (bfd *abfd, const char *name, struct bfd_link_info *link_info)
{
  lang_input_statement_type *fake_file;

  fake_file = lang_add_input_file (name,
				   lang_input_file_is_fake_enum,
				   NULL);
  fake_file->the_bfd = abfd;
  ldlang_add_file (fake_file);

  if (!bfd_link_add_symbols (abfd, link_info))
    einfo ("%Xaddsym %s: %E\n", name);
}