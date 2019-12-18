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
struct TYPE_2__ {int /*<<< orphan*/  avail_in; int /*<<< orphan*/ * next_in; } ;
struct zlib_trans_stream {int inited; int /*<<< orphan*/  ex; TYPE_1__ z; } ;

/* Variables and functions */
 int /*<<< orphan*/  inflateInit2 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zlib_inflate_set_in(void *data, const uint8_t *in, uint32_t in_size)
{
   struct zlib_trans_stream *z = (struct zlib_trans_stream *) data;

   if (!z)
      return;

   z->z.next_in                = (uint8_t *) in;
   z->z.avail_in               = in_size;
   if (!z->inited)
   {
      inflateInit2(&z->z, z->ex);
      z->inited = true;
   }
}