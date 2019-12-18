#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  path ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {TYPE_4__* backend; scalar_t__ directory; scalar_t__ footer; int /*<<< orphan*/  handle; int /*<<< orphan*/  data; scalar_t__ archive_size; } ;
typedef  TYPE_1__ file_archive_transfer_t ;
struct TYPE_6__ {int (* archive_parse_file_init ) (TYPE_1__*,char*) ;} ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  file_archive_data (int /*<<< orphan*/ ) ; 
 TYPE_4__* file_archive_get_file_backend (char*) ; 
 int /*<<< orphan*/  file_archive_open (char*) ; 
 scalar_t__ file_archive_size (int /*<<< orphan*/ ) ; 
 scalar_t__ path_get_archive_delim (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int stub1 (TYPE_1__*,char*) ; 

__attribute__((used)) static int file_archive_parse_file_init(file_archive_transfer_t *state,
      const char *file)
{
   char path[PATH_MAX_LENGTH];
   char *last                 = NULL;

   path[0] = '\0';

   strlcpy(path, file, sizeof(path));

   last = (char*)path_get_archive_delim(path);

   if (last)
      *last = '\0';

   state->backend = file_archive_get_file_backend(path);
   if (!state->backend)
      return -1;

   state->handle = file_archive_open(path);
   if (!state->handle)
      return -1;

   state->archive_size = (int32_t)file_archive_size(state->handle);
   state->data         = file_archive_data(state->handle);
   state->footer       = 0;
   state->directory    = 0;

   return state->backend->archive_parse_file_init(state, path);
}