#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {scalar_t__ NumFiles; size_t NumPackStreams; scalar_t__* PackSizes; TYPE_3__* Files; } ;
struct TYPE_9__ {TYPE_1__ db; } ;
struct sevenzip_context_t {int index; size_t packIndex; TYPE_5__ db; } ;
struct archive_extract_userdata {int dummy; } ;
typedef  int /*<<< orphan*/  infile ;
struct TYPE_7__ {scalar_t__ stream; } ;
typedef  TYPE_2__ file_archive_transfer_t ;
struct TYPE_8__ {scalar_t__ Size; scalar_t__ Crc; int /*<<< orphan*/  IsDir; } ;
typedef  scalar_t__ SRes ;
typedef  TYPE_3__ CSzFileItem ;

/* Variables and functions */
 unsigned int ARCHIVE_MODE_COMPRESSED ; 
 size_t PATH_MAX_LENGTH ; 
 scalar_t__ SZ_ERROR_FAIL ; 
 scalar_t__ SZ_OK ; 
 size_t SzArEx_GetFileNameUtf16 (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 scalar_t__ utf16_to_char_string (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int sevenzip_parse_file_iterate_step_internal(
      file_archive_transfer_t *state, char *filename,
      const uint8_t **cdata, unsigned *cmode,
      uint32_t *size, uint32_t *csize, uint32_t *checksum,
      unsigned *payback, struct archive_extract_userdata *userdata)
{
   struct sevenzip_context_t *sevenzip_context = (struct sevenzip_context_t*)state->stream;
   const CSzFileItem *file = sevenzip_context->db.db.Files + sevenzip_context->index;

   if (sevenzip_context->index < sevenzip_context->db.db.NumFiles)
   {
      size_t len = SzArEx_GetFileNameUtf16(&sevenzip_context->db,
            sevenzip_context->index, NULL);
      uint64_t compressed_size = 0;

      if (sevenzip_context->packIndex < sevenzip_context->db.db.NumPackStreams)
      {
         compressed_size = sevenzip_context->db.db.PackSizes[sevenzip_context->packIndex];
         sevenzip_context->packIndex++;
      }

      if (len < PATH_MAX_LENGTH && !file->IsDir)
      {
         char infile[PATH_MAX_LENGTH];
         SRes res                     = SZ_ERROR_FAIL;
         uint16_t *temp               = (uint16_t*)malloc(len * sizeof(uint16_t));

         if (!temp)
            return -1;

         infile[0] = '\0';

         SzArEx_GetFileNameUtf16(&sevenzip_context->db, sevenzip_context->index,
               temp);

         if (temp)
         {
            res  = utf16_to_char_string(temp, infile, sizeof(infile))
               ? SZ_OK : SZ_ERROR_FAIL;
            free(temp);
         }

         if (res != SZ_OK)
            return -1;

         strlcpy(filename, infile, PATH_MAX_LENGTH);

         *cmode    = ARCHIVE_MODE_COMPRESSED;
         *checksum = file->Crc;
         *size     = (uint32_t)file->Size;
         *csize    = (uint32_t)compressed_size;
      }
   }
   else
      return 0;

   *payback = 1;

   return 1;
}