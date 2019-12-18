#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char interface_id; size_t cmd_len; unsigned char* cmdp; size_t dxfer_len; unsigned char* sbp; size_t mx_sb_len; int timeout; int info; void* dxferp; int /*<<< orphan*/  dxfer_direction; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ sg_io_hdr_t ;
struct TYPE_6__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_2__ libretro_vfs_implementation_file ;
typedef  int CDROM_CMD_Direction ;

/* Variables and functions */
#define  DIRECTION_IN 130 
#define  DIRECTION_NONE 129 
#define  DIRECTION_OUT 128 
 int /*<<< orphan*/  SG_DXFER_FROM_DEV ; 
 int /*<<< orphan*/  SG_DXFER_NONE ; 
 int /*<<< orphan*/  SG_DXFER_TO_DEV ; 
 int SG_INFO_CHECK ; 
 int /*<<< orphan*/  SG_IO ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int cdrom_send_command_linux(const libretro_vfs_implementation_file *stream, CDROM_CMD_Direction dir, void *buf, size_t len, unsigned char *cmd, size_t cmd_len, unsigned char *sense, size_t sense_len)
{
   sg_io_hdr_t sgio = {0};
   int rv;

   switch (dir)
   {
      case DIRECTION_IN:
         sgio.dxfer_direction = SG_DXFER_FROM_DEV;
         break;
      case DIRECTION_OUT:
         sgio.dxfer_direction = SG_DXFER_TO_DEV;
         break;
      case DIRECTION_NONE:
      default:
         sgio.dxfer_direction = SG_DXFER_NONE;
         break;
   }

   sgio.interface_id = 'S';
   sgio.cmd_len = cmd_len;
   sgio.cmdp = cmd;
   sgio.dxferp = buf;
   sgio.dxfer_len = len;
   sgio.sbp = sense;
   sgio.mx_sb_len = sense_len;
   sgio.timeout = 5000;

   rv = ioctl(fileno(stream->fp), SG_IO, &sgio);

   if (rv == -1 || sgio.info & SG_INFO_CHECK)
      return 1;

   return 0;
}