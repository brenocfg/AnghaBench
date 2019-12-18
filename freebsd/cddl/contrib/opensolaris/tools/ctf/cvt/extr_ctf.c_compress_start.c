#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ voidpf ;
struct TYPE_5__ {scalar_t__ opaque; scalar_t__ zfree; scalar_t__ zalloc; } ;
struct TYPE_4__ {TYPE_2__ rb_zstr; } ;
typedef  TYPE_1__ resbuf_t ;
typedef  scalar_t__ free_func ;
typedef  scalar_t__ alloc_func ;

/* Variables and functions */
 int /*<<< orphan*/  Z_BEST_COMPRESSION ; 
 int Z_OK ; 
 int deflateInit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parseterminate (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zError (int) ; 

__attribute__((used)) static void
compress_start(resbuf_t *rb)
{
	int rc;

	rb->rb_zstr.zalloc = (alloc_func)0;
	rb->rb_zstr.zfree = (free_func)0;
	rb->rb_zstr.opaque = (voidpf)0;

	if ((rc = deflateInit(&rb->rb_zstr, Z_BEST_COMPRESSION)) != Z_OK)
		parseterminate("zlib start failed: %s", zError(rc));
}