#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_size; } ;
struct TYPE_19__ {int /*<<< orphan*/  language; } ;
struct TYPE_17__ {TYPE_8__* userdata; } ;
struct TYPE_18__ {TYPE_6__ res_info; TYPE_4__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ rc_res_resource ;
typedef  TYPE_6__ rc_res_res_info ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
struct TYPE_20__ {TYPE_1__ u; scalar_t__ named; } ;
typedef  TYPE_7__ rc_res_id ;
struct TYPE_15__ {int length; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {TYPE_2__ buffer; } ;
struct TYPE_21__ {TYPE_3__ u; int /*<<< orphan*/  type; int /*<<< orphan*/ * next; } ;
typedef  TYPE_8__ rc_rcdata_item ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_RB ; 
 int /*<<< orphan*/  RCDATA_BUFFER ; 
 int /*<<< orphan*/  RES_TYPE_USERDATA ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_5__* define_resource (int /*<<< orphan*/ *,int,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * open_file_search (char const*,int /*<<< orphan*/ ,char*,char**) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  resources ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
define_user_file (rc_res_id id, rc_res_id type,
		  const rc_res_res_info *resinfo, const char *filename)
{
  FILE *e;
  char *real_filename;
  struct stat s;
  bfd_byte *data;
  rc_res_id ids[3];
  rc_res_resource *r;

  e = open_file_search (filename, FOPEN_RB, "file", &real_filename);

  if (stat (real_filename, &s) < 0)
    fatal (_("stat failed on file `%s': %s"), real_filename,
	   strerror (errno));

  data = (bfd_byte *) res_alloc (s.st_size);

  get_data (e, data, s.st_size, real_filename);

  fclose (e);
  free (real_filename);

  ids[0] = type;
  ids[1] = id;
  ids[2].named = 0;
  ids[2].u.id = resinfo->language;

  r = define_resource (&resources, 3, ids, 0);
  r->type = RES_TYPE_USERDATA;
  r->u.userdata = ((rc_rcdata_item *)
		   res_alloc (sizeof (rc_rcdata_item)));
  r->u.userdata->next = NULL;
  r->u.userdata->type = RCDATA_BUFFER;
  r->u.userdata->u.buffer.length = s.st_size;
  r->u.userdata->u.buffer.data = data;
  r->res_info = *resinfo;
}