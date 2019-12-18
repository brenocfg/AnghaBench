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
struct TYPE_3__ {int /*<<< orphan*/  fr_address; int /*<<< orphan*/  fr_literal; } ;
typedef  TYPE_1__ fragS ;
typedef  int bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  arelent ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad_where (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int bfd_install_relocation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
#define  bfd_reloc_ok 130 
#define  bfd_reloc_outofrange 129 
#define  bfd_reloc_overflow 128 
 int /*<<< orphan*/  stdoutput ; 

__attribute__((used)) static void
install_reloc (asection *sec, arelent *reloc, fragS *fragp,
	       char *file, unsigned int line)
{
  char *err;
  bfd_reloc_status_type s;

  s = bfd_install_relocation (stdoutput, reloc,
			      fragp->fr_literal, fragp->fr_address,
			      sec, &err);
  switch (s)
    {
    case bfd_reloc_ok:
      break;
    case bfd_reloc_overflow:
      as_bad_where (file, line, _("relocation overflow"));
      break;
    case bfd_reloc_outofrange:
      as_bad_where (file, line, _("relocation out of range"));
      break;
    default:
      as_fatal (_("%s:%u: bad return from bfd_install_relocation: %x"),
		file, line, s);
    }
}