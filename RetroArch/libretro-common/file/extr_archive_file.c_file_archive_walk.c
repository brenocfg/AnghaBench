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
struct archive_extract_userdata {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * backend; int /*<<< orphan*/ * data; int /*<<< orphan*/ * directory; int /*<<< orphan*/ * footer; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * handle; scalar_t__ archive_size; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ file_archive_transfer_t ;
typedef  int /*<<< orphan*/  file_archive_file_cb ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_TRANSFER_INIT ; 
 scalar_t__ file_archive_parse_file_iterate (TYPE_1__*,int*,char const*,char const*,int /*<<< orphan*/ ,struct archive_extract_userdata*) ; 

__attribute__((used)) static bool file_archive_walk(const char *file, const char *valid_exts,
      file_archive_file_cb file_cb, struct archive_extract_userdata *userdata)
{
   file_archive_transfer_t state;
   bool returnerr                = true;

   state.type                    = ARCHIVE_TRANSFER_INIT;
   state.archive_size            = 0;
   state.handle                  = NULL;
   state.stream                  = NULL;
   state.footer                  = NULL;
   state.directory               = NULL;
   state.data                    = NULL;
   state.backend                 = NULL;

   for (;;)
   {
      if (file_archive_parse_file_iterate(&state, &returnerr, file,
            valid_exts, file_cb, userdata) != 0)
         break;
   }

   return returnerr;
}