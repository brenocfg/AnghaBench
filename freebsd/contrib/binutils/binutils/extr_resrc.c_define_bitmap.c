#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ rc_uint_type ;
struct TYPE_10__ {int /*<<< orphan*/  language; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct TYPE_8__ {TYPE_1__ data; } ;
struct TYPE_9__ {TYPE_4__ res_info; TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ rc_res_resource ;
typedef  TYPE_4__ rc_res_res_info ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ BITMAP_SKIP ; 
 int /*<<< orphan*/  FOPEN_RB ; 
 int /*<<< orphan*/  RES_TYPE_BITMAP ; 
 int /*<<< orphan*/  RT_BITMAP ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_file_search (char const*,int /*<<< orphan*/ ,char*,char**) ; 
 scalar_t__ res_alloc (scalar_t__) ; 
 int /*<<< orphan*/  resources ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
define_bitmap (rc_res_id id, const rc_res_res_info *resinfo,
	       const char *filename)
{
  FILE *e;
  char *real_filename;
  struct stat s;
  bfd_byte *data;
  rc_uint_type i;
  rc_res_resource *r;

  e = open_file_search (filename, FOPEN_RB, "bitmap file", &real_filename);

  if (stat (real_filename, &s) < 0)
    fatal (_("stat failed on bitmap file `%s': %s"), real_filename,
	   strerror (errno));

  data = (bfd_byte *) res_alloc (s.st_size - BITMAP_SKIP);

  for (i = 0; i < BITMAP_SKIP; i++)
    getc (e);

  get_data (e, data, s.st_size - BITMAP_SKIP, real_filename);

  fclose (e);
  free (real_filename);

  r = define_standard_resource (&resources, RT_BITMAP, id,
				resinfo->language, 0);

  r->type = RES_TYPE_BITMAP;
  r->u.data.length = s.st_size - BITMAP_SKIP;
  r->u.data.data = data;
  r->res_info = *resinfo;
}