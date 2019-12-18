#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elf_link_hash_entry {scalar_t__ type; int def_regular; int /*<<< orphan*/  other; } ;
struct elf_backend_data {int /*<<< orphan*/  (* elf_backend_hide_symbol ) (struct bfd_link_info*,struct elf_link_hash_entry*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  collect; } ;
struct bfd_link_info {int dummy; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_3__ {int /*<<< orphan*/ * tls_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_LOCAL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ STT_TLS ; 
 int /*<<< orphan*/  STV_HIDDEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfd_link_hash_entry**) ; 
 TYPE_1__* elf_hash_table (struct bfd_link_info*) ; 
 struct elf_link_hash_entry* elf_link_hash_lookup (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bfd_link_info*,struct elf_link_hash_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
elf_i386_always_size_sections (bfd *output_bfd,
			       struct bfd_link_info *info)
{
  asection *tls_sec = elf_hash_table (info)->tls_sec;

  if (tls_sec)
    {
      struct elf_link_hash_entry *tlsbase;

      tlsbase = elf_link_hash_lookup (elf_hash_table (info),
				      "_TLS_MODULE_BASE_",
				      FALSE, FALSE, FALSE);

      if (tlsbase && tlsbase->type == STT_TLS)
	{
	  struct bfd_link_hash_entry *bh = NULL;
	  const struct elf_backend_data *bed
	    = get_elf_backend_data (output_bfd);

	  if (!(_bfd_generic_link_add_one_symbol
		(info, output_bfd, "_TLS_MODULE_BASE_", BSF_LOCAL,
		 tls_sec, 0, NULL, FALSE,
		 bed->collect, &bh)))
	    return FALSE;
	  tlsbase = (struct elf_link_hash_entry *)bh;
	  tlsbase->def_regular = 1;
	  tlsbase->other = STV_HIDDEN;
	  (*bed->elf_backend_hide_symbol) (info, tlsbase, TRUE);
	}
    }

  return TRUE;
}