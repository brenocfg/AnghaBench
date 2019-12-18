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
struct TYPE_3__ {scalar_t__ avail_in; int /*<<< orphan*/ * next_in; int /*<<< orphan*/  workspace; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ initialized ; 
 TYPE_1__ stream ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_inflateInit (TYPE_1__*) ; 
 int /*<<< orphan*/  zlib_inflate_workspacesize () ; 

int cramfs_uncompress_init(void)
{
	if (!initialized++) {
		stream.workspace = vmalloc(zlib_inflate_workspacesize());
		if ( !stream.workspace ) {
			initialized = 0;
			return -ENOMEM;
		}
		stream.next_in = NULL;
		stream.avail_in = 0;
		zlib_inflateInit(&stream);
	}
	return 0;
}