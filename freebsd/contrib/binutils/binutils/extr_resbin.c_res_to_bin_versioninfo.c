#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
struct bin_versioninfo {struct bin_versioninfo* sig2; struct bin_versioninfo* fixed_size; struct bin_versioninfo* size; struct bin_versioninfo* sig1; struct bin_versioninfo* file_date_ls; struct bin_versioninfo* file_date_ms; struct bin_versioninfo* file_subtype; struct bin_versioninfo* file_type; struct bin_versioninfo* file_os; struct bin_versioninfo* file_flags; struct bin_versioninfo* file_flags_mask; struct bin_versioninfo* product_version_ls; struct bin_versioninfo* product_version_ms; struct bin_versioninfo* file_version_ls; struct bin_versioninfo* file_version; } ;
struct bin_ver_info {struct bin_ver_info* sig2; struct bin_ver_info* fixed_size; struct bin_ver_info* size; struct bin_ver_info* sig1; struct bin_ver_info* file_date_ls; struct bin_ver_info* file_date_ms; struct bin_ver_info* file_subtype; struct bin_ver_info* file_type; struct bin_ver_info* file_os; struct bin_ver_info* file_flags; struct bin_ver_info* file_flags_mask; struct bin_ver_info* product_version_ls; struct bin_ver_info* product_version_ms; struct bin_ver_info* file_version_ls; struct bin_ver_info* file_version; } ;
struct bin_fixed_versioninfo {struct bin_fixed_versioninfo* sig2; struct bin_fixed_versioninfo* fixed_size; struct bin_fixed_versioninfo* size; struct bin_fixed_versioninfo* sig1; struct bin_fixed_versioninfo* file_date_ls; struct bin_fixed_versioninfo* file_date_ms; struct bin_fixed_versioninfo* file_subtype; struct bin_fixed_versioninfo* file_type; struct bin_fixed_versioninfo* file_os; struct bin_fixed_versioninfo* file_flags; struct bin_fixed_versioninfo* file_flags_mask; struct bin_fixed_versioninfo* product_version_ls; struct bin_fixed_versioninfo* product_version_ms; struct bin_fixed_versioninfo* file_version_ls; struct bin_fixed_versioninfo* file_version; } ;
struct TYPE_13__ {TYPE_8__* fixed; TYPE_7__* var; } ;
typedef  TYPE_4__ rc_versioninfo ;
struct TYPE_14__ {int language; int charset; struct TYPE_14__* next; } ;
typedef  TYPE_5__ rc_ver_varinfo ;
struct TYPE_15__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; struct TYPE_15__* next; } ;
typedef  TYPE_6__ rc_ver_stringinfo ;
struct TYPE_12__ {TYPE_5__* var; int /*<<< orphan*/  key; } ;
struct TYPE_10__ {TYPE_6__* strings; int /*<<< orphan*/  language; } ;
struct TYPE_11__ {TYPE_3__ var; TYPE_1__ string; } ;
struct TYPE_16__ {int type; TYPE_2__ u; struct TYPE_16__* next; } ;
typedef  TYPE_7__ rc_ver_info ;
typedef  int rc_uint_type ;
struct TYPE_17__ {int file_version_ms; int file_version_ls; int product_version_ms; int product_version_ls; int file_flags_mask; int file_flags; int file_os; int file_type; int file_subtype; int file_date_ms; int file_date_ls; } ;
typedef  TYPE_8__ rc_fixed_versioninfo ;
typedef  struct bin_versioninfo bfd_byte ;

/* Variables and functions */
 int BIN_FIXED_VERSIONINFO_SIZE ; 
 int BIN_VERSIONINFO_SIZE ; 
 int BIN_VER_INFO_SIZE ; 
#define  VERINFO_STRING 129 
#define  VERINFO_VAR 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,struct bin_versioninfo*,int,int) ; 
 int string_to_unicode_bin (int /*<<< orphan*/ *,int,char*) ; 
 int unicode_to_bin (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,struct bin_versioninfo*,int) ; 
 int /*<<< orphan*/  windres_put_32 (int /*<<< orphan*/ *,struct bin_versioninfo*,int) ; 

__attribute__((used)) static rc_uint_type
res_to_bin_versioninfo (windres_bfd *wrbfd, rc_uint_type off,
			const rc_versioninfo *versioninfo)
{
  rc_uint_type off_delta = off;
  rc_uint_type start;
  struct bin_versioninfo bvi;
  rc_ver_info *vi;

  start = off;
  off += BIN_VERSIONINFO_SIZE;
  off = string_to_unicode_bin (wrbfd, off, "VS_VERSION_INFO");
  off += (4 - ((off - off_delta) & 3)) & 3;

  if (versioninfo->fixed != NULL)
    {
      if (wrbfd)
	{
	  struct bin_fixed_versioninfo bfv;
	  const rc_fixed_versioninfo *fi;

      fi = versioninfo->fixed;
	  windres_put_32 (wrbfd, bfv.sig1, 0xfeef04bd);
	  windres_put_32 (wrbfd, bfv.sig2, 0x10000);
	  windres_put_32 (wrbfd, bfv.file_version, fi->file_version_ms);
	  windres_put_32 (wrbfd, bfv.file_version_ls, fi->file_version_ls);
	  windres_put_32 (wrbfd, bfv.product_version_ms, fi->product_version_ms);
	  windres_put_32 (wrbfd, bfv.product_version_ls, fi->product_version_ls);
	  windres_put_32 (wrbfd, bfv.file_flags_mask, fi->file_flags_mask);
	  windres_put_32 (wrbfd, bfv.file_flags, fi->file_flags);
	  windres_put_32 (wrbfd, bfv.file_os, fi->file_os);
	  windres_put_32 (wrbfd, bfv.file_type, fi->file_type);
	  windres_put_32 (wrbfd, bfv.file_subtype, fi->file_subtype);
	  windres_put_32 (wrbfd, bfv.file_date_ms, fi->file_date_ms);
	  windres_put_32 (wrbfd, bfv.file_date_ls, fi->file_date_ls);
	  set_windres_bfd_content (wrbfd, &bfv, off, BIN_FIXED_VERSIONINFO_SIZE);
	}
      off += BIN_FIXED_VERSIONINFO_SIZE;
    }

  for (vi = versioninfo->var; vi != NULL; vi = vi->next)
    {
      struct bin_ver_info bv;
      rc_uint_type bv_off;

      off += (4 - ((off - off_delta) & 3)) & 3;

      bv_off = off;

      off += BIN_VER_INFO_SIZE;

      switch (vi->type)
	{
	default:
	  abort ();
	case VERINFO_STRING:
	  {
	    struct bin_ver_info bvsd;
	    rc_uint_type vs_off;
	    const rc_ver_stringinfo *vs;

	    off = string_to_unicode_bin (wrbfd, off, "StringFileInfo");
	    off += (4 - ((off - off_delta) & 3)) & 3;

	    vs_off = off;

	    off += BIN_VER_INFO_SIZE;

	    off = unicode_to_bin (wrbfd, off, vi->u.string.language);

	    for (vs = vi->u.string.strings; vs != NULL; vs = vs->next)
	      {
		struct bin_ver_info bvss;
		rc_uint_type vss_off,str_off;

		off += (4 - ((off - off_delta) & 3)) & 3;

		vss_off = off;
		off += BIN_VER_INFO_SIZE;

		off = unicode_to_bin (wrbfd, off, vs->key);

		off += (4 - ((off - off_delta) & 3)) & 3;

		str_off = off;
		off = unicode_to_bin (wrbfd, off, vs->value);
		if (wrbfd)
		  {
		    windres_put_16 (wrbfd, bvss.size, off - vss_off);
		    windres_put_16 (wrbfd, bvss.sig1, (off - str_off) / 2);
		    windres_put_16 (wrbfd, bvss.sig2, 1);
		    set_windres_bfd_content (wrbfd, &bvss, vss_off,
		    			     BIN_VER_INFO_SIZE);
		  }
	      }
	    if (wrbfd)
	      {
		windres_put_16 (wrbfd, bvsd.size, off - vs_off);
		windres_put_16 (wrbfd, bvsd.sig1, 0);
		windres_put_16 (wrbfd, bvsd.sig2, 0);
		set_windres_bfd_content (wrbfd, &bvsd, vs_off,
					 BIN_VER_INFO_SIZE);
	      }
	    break;
	  }

	case VERINFO_VAR:
	  {
	    rc_uint_type vvd_off, vvvd_off;
	    struct bin_ver_info bvvd;
	    const rc_ver_varinfo *vv;

	    off = string_to_unicode_bin (wrbfd, off, "VarFileInfo");

	    off += (4 - ((off - off_delta) & 3)) & 3;

	    vvd_off = off;
	    off += BIN_VER_INFO_SIZE;

	    off = unicode_to_bin (wrbfd, off, vi->u.var.key);

	    off += (4 - ((off - off_delta) & 3)) & 3;

	    vvvd_off = off;

	    for (vv = vi->u.var.var; vv != NULL; vv = vv->next)
	      {
		if (wrbfd)
		  {
		    bfd_byte vvsd[4];

		    windres_put_16 (wrbfd, &vvsd[0], vv->language);
		    windres_put_16 (wrbfd, &vvsd[2], vv->charset);
		    set_windres_bfd_content (wrbfd, vvsd, off, 4);
		  }
		off += 4;
	      }
	    if (wrbfd)
	    {
		windres_put_16 (wrbfd, bvvd.size, off - vvd_off);
		windres_put_16 (wrbfd, bvvd.sig1, off - vvvd_off);
		windres_put_16 (wrbfd, bvvd.sig2, 0);
		set_windres_bfd_content (wrbfd, &bvvd, vvd_off,
					 BIN_VER_INFO_SIZE);
	    }

	    break;
	  }
	}

      if (wrbfd)
	{
	  windres_put_16 (wrbfd, bv.size, off-bv_off);
	  windres_put_16 (wrbfd, bv.sig1, 0);
	  windres_put_16 (wrbfd, bv.sig2, 0);
	  set_windres_bfd_content (wrbfd, &bv, bv_off,
	  			   BIN_VER_INFO_SIZE);
	}
    }

  if (wrbfd)
    {
      windres_put_16 (wrbfd, bvi.size, off - start);
      windres_put_16 (wrbfd, bvi.fixed_size,
		      versioninfo->fixed == NULL ? 0
		      				 : BIN_FIXED_VERSIONINFO_SIZE);
      windres_put_16 (wrbfd, bvi.sig2, 0);
      set_windres_bfd_content (wrbfd, &bvi, start, BIN_VER_INFO_SIZE);
    }
  return off;
}