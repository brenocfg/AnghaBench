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
struct TYPE_4__ {int /*<<< orphan*/  rb_zstr; } ;
typedef  TYPE_1__ resbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int /*<<< orphan*/  compress_flush (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parseterminate (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zError (int) ; 

__attribute__((used)) static void
compress_end(resbuf_t *rb)
{
	int rc;

	compress_flush(rb, Z_FINISH);

	if ((rc = deflateEnd(&rb->rb_zstr)) != Z_OK)
		parseterminate("zlib end failed: %s", zError(rc));
}