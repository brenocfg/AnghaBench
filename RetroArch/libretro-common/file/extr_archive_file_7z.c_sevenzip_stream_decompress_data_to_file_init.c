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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sevenzip_context_t {TYPE_1__* handle; } ;
struct TYPE_3__ {scalar_t__ stream; } ;
typedef  TYPE_1__ file_archive_file_handle_t ;

/* Variables and functions */

__attribute__((used)) static bool sevenzip_stream_decompress_data_to_file_init(
      file_archive_file_handle_t *handle,
      const uint8_t *cdata,  uint32_t csize, uint32_t size)
{
   struct sevenzip_context_t *sevenzip_context =
         (struct sevenzip_context_t*)handle->stream;

   if (!sevenzip_context)
      return false;

   sevenzip_context->handle = handle;

   return true;
}