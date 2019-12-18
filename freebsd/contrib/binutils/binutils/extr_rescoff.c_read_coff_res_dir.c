#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  void* unichar ;
struct extern_res_entry {int /*<<< orphan*/  rva; int /*<<< orphan*/  name; } ;
struct extern_res_directory {int /*<<< orphan*/  const* id_count; int /*<<< orphan*/  const* name_count; int /*<<< orphan*/  const* minor; int /*<<< orphan*/  const* major; int /*<<< orphan*/  time; int /*<<< orphan*/  characteristics; } ;
struct coff_file_info {int /*<<< orphan*/  const* data; int /*<<< orphan*/  const* data_end; } ;
typedef  int rc_uint_type ;
struct TYPE_10__ {int length; void** name; } ;
struct TYPE_11__ {unsigned long id; TYPE_1__ n; } ;
struct TYPE_13__ {int named; TYPE_2__ u; } ;
typedef  TYPE_4__ rc_res_id ;
struct TYPE_12__ {void* res; TYPE_6__* dir; } ;
struct TYPE_14__ {int subdir; struct TYPE_14__* next; TYPE_3__ u; TYPE_4__ id; } ;
typedef  TYPE_5__ rc_res_entry ;
struct TYPE_15__ {TYPE_5__* entries; void* minor; void* major; void* time; void* characteristics; } ;
typedef  TYPE_6__ rc_res_directory ;
typedef  int /*<<< orphan*/  const bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  overrun (struct coff_file_info const*,int /*<<< orphan*/ ) ; 
 void* read_coff_data_entry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,struct coff_file_info const*,TYPE_4__ const*) ; 
 scalar_t__ res_alloc (int) ; 
 void* windres_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 void* windres_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rc_res_directory *
read_coff_res_dir (windres_bfd *wrbfd, const bfd_byte *data,
		   const struct coff_file_info *finfo,
		   const rc_res_id *type, int level)
{
  const struct extern_res_directory *erd;
  rc_res_directory *rd;
  int name_count, id_count, i;
  rc_res_entry **pp;
  const struct extern_res_entry *ere;

  if ((size_t) (finfo->data_end - data) < sizeof (struct extern_res_directory))
    overrun (finfo, _("directory"));

  erd = (const struct extern_res_directory *) data;

  rd = (rc_res_directory *) res_alloc (sizeof (rc_res_directory));
  rd->characteristics = windres_get_32 (wrbfd, erd->characteristics, 4);
  rd->time = windres_get_32 (wrbfd, erd->time, 4);
  rd->major = windres_get_16 (wrbfd, erd->major, 2);
  rd->minor = windres_get_16 (wrbfd, erd->minor, 2);
  rd->entries = NULL;

  name_count = windres_get_16 (wrbfd, erd->name_count, 2);
  id_count = windres_get_16 (wrbfd, erd->id_count, 2);

  pp = &rd->entries;

  /* The resource directory entries immediately follow the directory
     table.  */
  ere = (const struct extern_res_entry *) (erd + 1);

  for (i = 0; i < name_count; i++, ere++)
    {
      rc_uint_type name, rva;
      rc_res_entry *re;
      const bfd_byte *ers;
      int length, j;

      if ((const bfd_byte *) ere >= finfo->data_end)
	overrun (finfo, _("named directory entry"));

      name = windres_get_32 (wrbfd, ere->name, 4);
      rva = windres_get_32 (wrbfd, ere->rva, 4);

      /* For some reason the high bit in NAME is set.  */
      name &=~ 0x80000000;

      if (name > (rc_uint_type) (finfo->data_end - finfo->data))
	overrun (finfo, _("directory entry name"));

      ers = finfo->data + name;

      re = (rc_res_entry *) res_alloc (sizeof *re);
      re->next = NULL;
      re->id.named = 1;
      length = windres_get_16 (wrbfd, ers, 2);
      re->id.u.n.length = length;
      re->id.u.n.name = (unichar *) res_alloc (length * sizeof (unichar));
      for (j = 0; j < length; j++)
	re->id.u.n.name[j] = windres_get_16 (wrbfd, ers + j * 2 + 2, 2);

      if (level == 0)
	type = &re->id;

      if ((rva & 0x80000000) != 0)
	{
	  rva &=~ 0x80000000;
	  if (rva >= (rc_uint_type) (finfo->data_end - finfo->data))
	    overrun (finfo, _("named subdirectory"));
	  re->subdir = 1;
	  re->u.dir = read_coff_res_dir (wrbfd, finfo->data + rva, finfo, type,
					 level + 1);
	}
      else
	{
	  if (rva >= (rc_uint_type) (finfo->data_end - finfo->data))
	    overrun (finfo, _("named resource"));
	  re->subdir = 0;
	  re->u.res = read_coff_data_entry (wrbfd, finfo->data + rva, finfo, type);
	}

      *pp = re;
      pp = &re->next;
    }

  for (i = 0; i < id_count; i++, ere++)
    {
      unsigned long name, rva;
      rc_res_entry *re;

      if ((const bfd_byte *) ere >= finfo->data_end)
	overrun (finfo, _("ID directory entry"));

      name = windres_get_32 (wrbfd, ere->name, 4);
      rva = windres_get_32 (wrbfd, ere->rva, 4);

      re = (rc_res_entry *) res_alloc (sizeof *re);
      re->next = NULL;
      re->id.named = 0;
      re->id.u.id = name;

      if (level == 0)
	type = &re->id;

      if ((rva & 0x80000000) != 0)
	{
	  rva &=~ 0x80000000;
	  if (rva >= (rc_uint_type) (finfo->data_end - finfo->data))
	    overrun (finfo, _("ID subdirectory"));
	  re->subdir = 1;
	  re->u.dir = read_coff_res_dir (wrbfd, finfo->data + rva, finfo, type,
					 level + 1);
	}
      else
	{
	  if (rva >= (rc_uint_type) (finfo->data_end - finfo->data))
	    overrun (finfo, _("ID resource"));
	  re->subdir = 0;
	  re->u.res = read_coff_data_entry (wrbfd, finfo->data + rva, finfo, type);
	}

      *pp = re;
      pp = &re->next;
    }

  return rd;
}