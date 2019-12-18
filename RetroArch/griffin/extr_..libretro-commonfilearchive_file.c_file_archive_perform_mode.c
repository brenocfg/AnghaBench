#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct archive_extract_userdata {int /*<<< orphan*/  archive_path; int /*<<< orphan*/  context; } ;
struct TYPE_5__ {int /*<<< orphan*/  stream; TYPE_3__* backend; int /*<<< orphan*/  real_checksum; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ file_archive_file_handle_t ;
struct TYPE_6__ {int (* stream_decompress_data_to_file_iterate ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stream_decompress_data_to_file_init ) (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  ARCHIVE_MODE_COMPRESSED 129 
#define  ARCHIVE_MODE_UNCOMPRESSED 128 
 int /*<<< orphan*/  file_archive_decompress_data_to_file (TYPE_1__*,int,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* file_archive_get_file_backend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filestream_write_file (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

bool file_archive_perform_mode(const char *path, const char *valid_exts,
      const uint8_t *cdata, unsigned cmode, uint32_t csize, uint32_t size,
      uint32_t crc32, struct archive_extract_userdata *userdata)
{
   switch (cmode)
   {
      case ARCHIVE_MODE_UNCOMPRESSED:
         if (!filestream_write_file(path, cdata, size))
            return false;
         break;

      case ARCHIVE_MODE_COMPRESSED:
         {
            int ret = 0;
            file_archive_file_handle_t handle;

            handle.stream        = userdata->context;
            handle.data          = NULL;
            handle.real_checksum = 0;
            handle.backend       = file_archive_get_file_backend(userdata->archive_path);

            if (!handle.backend)
               return false;

            if (!handle.backend->stream_decompress_data_to_file_init(&handle,
                     cdata, csize, size))
               return false;

            do
            {
               ret = handle.backend->stream_decompress_data_to_file_iterate(
                     handle.stream);
            }while(ret == 0);

            if (!file_archive_decompress_data_to_file(&handle,
                     ret, path, valid_exts,
                     cdata, csize, size, crc32))
               return false;
         }
         break;
      default:
         return false;
   }

   return true;
}