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
typedef  scalar_t__ rc_uint_type ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  rc_res_directory ;
typedef  scalar_t__ bfd_signed_vma ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_WT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_rc_directory (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__*,int) ; 

void
write_rc_file (const char *filename, const rc_res_directory *resources)
{
  FILE *e;
  rc_uint_type language;

  if (filename == NULL)
    e = stdout;
  else
    {
      e = fopen (filename, FOPEN_WT);
      if (e == NULL)
	fatal (_("can't open `%s' for output: %s"), filename, strerror (errno));
    }

  language = (rc_uint_type) ((bfd_signed_vma) -1);
  write_rc_directory (e, resources, (const rc_res_id *) NULL,
		      (const rc_res_id *) NULL, &language, 1);
}