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
struct flist {int /*<<< orphan*/  name; scalar_t__ started_p; struct flist* next; int /*<<< orphan*/  f; } ;
typedef  int lang_bitmap ;

/* Variables and functions */
 size_t NUM_BASE_FILES ; 
 int /*<<< orphan*/ * base_files ; 
 int get_base_file_bitmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  put_mangled_filename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
finish_root_table (struct flist *flp, const char *pfx, const char *lastname,
		   const char *tname, const char *name)
{
  struct flist *fli2;

  for (fli2 = flp; fli2; fli2 = fli2->next)
    if (fli2->started_p)
      {
	oprintf (fli2->f, "  %s\n", lastname);
	oprintf (fli2->f, "};\n\n");
      }

  for (fli2 = flp; fli2; fli2 = fli2->next)
    if (fli2->started_p)
      {
	lang_bitmap bitmap = get_base_file_bitmap (fli2->name);
	int fnum;

	for (fnum = 0; bitmap != 0; fnum++, bitmap >>= 1)
	  if (bitmap & 1)
	    {
	      oprintf (base_files[fnum],
		       "extern const struct %s gt_%s_",
		       tname, pfx);
	      put_mangled_filename (base_files[fnum], fli2->name);
	      oprintf (base_files[fnum], "[];\n");
	    }
      }

  {
    size_t fnum;
    for (fnum = 0; fnum < NUM_BASE_FILES; fnum++)
      oprintf (base_files [fnum],
	       "const struct %s * const %s[] = {\n",
	       tname, name);
  }


  for (fli2 = flp; fli2; fli2 = fli2->next)
    if (fli2->started_p)
      {
	lang_bitmap bitmap = get_base_file_bitmap (fli2->name);
	int fnum;

	fli2->started_p = 0;

	for (fnum = 0; bitmap != 0; fnum++, bitmap >>= 1)
	  if (bitmap & 1)
	    {
	      oprintf (base_files[fnum], "  gt_%s_", pfx);
	      put_mangled_filename (base_files[fnum], fli2->name);
	      oprintf (base_files[fnum], ",\n");
	    }
      }

  {
    size_t fnum;
    for (fnum = 0; fnum < NUM_BASE_FILES; fnum++)
      {
	oprintf (base_files[fnum], "  NULL\n");
	oprintf (base_files[fnum], "};\n");
      }
  }
}