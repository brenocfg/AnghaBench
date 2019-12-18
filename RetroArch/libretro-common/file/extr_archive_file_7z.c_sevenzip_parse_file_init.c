#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_7__ {int /*<<< orphan*/  s; int /*<<< orphan*/ * realStream; } ;
struct TYPE_8__ {int /*<<< orphan*/  s; int /*<<< orphan*/  file; } ;
struct sevenzip_context_t {int /*<<< orphan*/  allocTempImp; int /*<<< orphan*/  allocImp; TYPE_3__ lookStream; int /*<<< orphan*/  db; TYPE_5__ archiveStream; } ;
struct TYPE_6__ {scalar_t__ archive_size; struct sevenzip_context_t* stream; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ file_archive_transfer_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrcGenerateTable () ; 
 int /*<<< orphan*/  FileInStream_CreateVTable (TYPE_5__*) ; 
 scalar_t__ InFile_Open (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ InFile_OpenW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LookToRead_CreateVTable (TYPE_3__*,int) ; 
 int /*<<< orphan*/  LookToRead_Init (TYPE_3__*) ; 
 int /*<<< orphan*/  SEVENZIP_MAGIC ; 
 scalar_t__ SEVENZIP_MAGIC_LEN ; 
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  SzArEx_Init (int /*<<< orphan*/ *) ; 
 scalar_t__ SzArEx_Open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sevenzip_stream_free (struct sevenzip_context_t*) ; 
 scalar_t__ sevenzip_stream_new () ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_not_equal_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * utf8_to_utf16_string_alloc (char const*) ; 

__attribute__((used)) static int sevenzip_parse_file_init(file_archive_transfer_t *state,
      const char *file)
{
   struct sevenzip_context_t *sevenzip_context =
         (struct sevenzip_context_t*)sevenzip_stream_new();

   if (state->archive_size < SEVENZIP_MAGIC_LEN)
      goto error;

   if (string_is_not_equal_fast(state->data, SEVENZIP_MAGIC, SEVENZIP_MAGIC_LEN))
      goto error;

   state->stream = sevenzip_context;

#if defined(_WIN32) && defined(USE_WINDOWS_FILE) && !defined(LEGACY_WIN32)
   if (!string_is_empty(file))
   {
      wchar_t *fileW = utf8_to_utf16_string_alloc(file);

      if (fileW)
      {
         /* could not open 7zip archive? */
         if (InFile_OpenW(&sevenzip_context->archiveStream.file, fileW))
         {
            free(fileW);
            goto error;
         }

         free(fileW);
      }
   }
#else
   /* could not open 7zip archive? */
   if (InFile_Open(&sevenzip_context->archiveStream.file, file))
      goto error;
#endif

   FileInStream_CreateVTable(&sevenzip_context->archiveStream);
   LookToRead_CreateVTable(&sevenzip_context->lookStream, false);
   sevenzip_context->lookStream.realStream = &sevenzip_context->archiveStream.s;
   LookToRead_Init(&sevenzip_context->lookStream);
   CrcGenerateTable();
   SzArEx_Init(&sevenzip_context->db);

   if (SzArEx_Open(&sevenzip_context->db, &sevenzip_context->lookStream.s,
         &sevenzip_context->allocImp, &sevenzip_context->allocTempImp) != SZ_OK)
      goto error;

   return 0;

error:
   if (sevenzip_context)
      sevenzip_stream_free(sevenzip_context);
   return -1;
}