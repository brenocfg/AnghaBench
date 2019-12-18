#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  avail_out; int /*<<< orphan*/ * next_out; } ;
struct zlib_trans_stream {TYPE_1__ z; } ;

/* Variables and functions */

__attribute__((used)) static void zlib_set_out(void *data, uint8_t *out, uint32_t out_size)
{
   struct zlib_trans_stream *z = (struct zlib_trans_stream *) data;

   if (!z)
      return;

   z->z.next_out               = out;
   z->z.avail_out              = out_size;
}