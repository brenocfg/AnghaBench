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
typedef  int /*<<< orphan*/  windres_bfd ;
struct bin_res_info {int /*<<< orphan*/  characteristics; int /*<<< orphan*/  version2; int /*<<< orphan*/  language; int /*<<< orphan*/  memflags; int /*<<< orphan*/  version; } ;
typedef  scalar_t__ rc_uint_type ;
struct TYPE_3__ {int /*<<< orphan*/  characteristics; int /*<<< orphan*/  version; int /*<<< orphan*/  language; int /*<<< orphan*/  memflags; } ;
typedef  TYPE_1__ rc_res_res_info ;

/* Variables and functions */
 scalar_t__ BIN_RES_INFO_SIZE ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,struct bin_res_info*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windres_put_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rc_uint_type
write_res_info (windres_bfd *wrbfd, rc_uint_type off, const rc_res_res_info *info)
{
  if (wrbfd)
    {
      struct bin_res_info l;
      
      windres_put_32 (wrbfd, l.version, info->version);
      windres_put_16 (wrbfd, l.memflags, info->memflags);
      windres_put_16 (wrbfd, l.language, info->language);
      windres_put_32 (wrbfd, l.version2, info->version);
      windres_put_32 (wrbfd, l.characteristics, info->characteristics);
      set_windres_bfd_content (wrbfd, &l, off, BIN_RES_INFO_SIZE);
    }
  return off + BIN_RES_INFO_SIZE;
}