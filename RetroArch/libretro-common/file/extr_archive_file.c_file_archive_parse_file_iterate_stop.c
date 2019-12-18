#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ file_archive_transfer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_TRANSFER_DEINIT ; 
 int /*<<< orphan*/  file_archive_parse_file_iterate (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void file_archive_parse_file_iterate_stop(file_archive_transfer_t *state)
{
   if (!state || !state->handle)
      return;

   state->type = ARCHIVE_TRANSFER_DEINIT;
   file_archive_parse_file_iterate(state, NULL, NULL, NULL, NULL, NULL);
}