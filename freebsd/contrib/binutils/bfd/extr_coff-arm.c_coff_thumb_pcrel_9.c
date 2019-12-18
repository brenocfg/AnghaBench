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
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  arelent ;

/* Variables and functions */
 int /*<<< orphan*/  b9 ; 
 int /*<<< orphan*/  coff_thumb_pcrel_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_reloc_status_type
coff_thumb_pcrel_9 (bfd *abfd,
		    arelent *reloc_entry,
		    asymbol *symbol,
		    void * data,
		    asection *input_section,
		    bfd *output_bfd,
		    char **error_message)
{
  return coff_thumb_pcrel_common (abfd, reloc_entry, symbol, data,
                                  input_section, output_bfd, error_message,
				  b9);
}