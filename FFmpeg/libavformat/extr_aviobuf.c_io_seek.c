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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ AVIOInternal ;

/* Variables and functions */
 int /*<<< orphan*/  ffurl_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int64_t io_seek(void *opaque, int64_t offset, int whence)
{
    AVIOInternal *internal = opaque;
    return ffurl_seek(internal->h, offset, whence);
}