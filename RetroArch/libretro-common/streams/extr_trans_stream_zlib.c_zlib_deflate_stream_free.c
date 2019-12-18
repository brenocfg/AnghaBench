#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct zlib_trans_stream {int /*<<< orphan*/  z; scalar_t__ inited; } ;

/* Variables and functions */
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct zlib_trans_stream*) ; 

__attribute__((used)) static void zlib_deflate_stream_free(void *data)
{
   struct zlib_trans_stream *z = (struct zlib_trans_stream *) data;
   if (!z)
      return;
   if (z->inited)
      deflateEnd(&z->z);
   free(z);
}