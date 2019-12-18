#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {TYPE_1__* prot; } ;
struct TYPE_5__ {TYPE_3__* h; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* url_read_seek ) (TYPE_3__*,int,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_2__ AVIOInternal ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int64_t io_read_seek(void *opaque, int stream_index, int64_t timestamp, int flags)
{
    AVIOInternal *internal = opaque;
    if (!internal->h->prot->url_read_seek)
        return AVERROR(ENOSYS);
    return internal->h->prot->url_read_seek(internal->h, stream_index, timestamp, flags);
}