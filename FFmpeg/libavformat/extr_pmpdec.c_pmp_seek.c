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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__ cur_stream; } ;
typedef  TYPE_1__ PMPContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */

__attribute__((used)) static int pmp_seek(AVFormatContext *s, int stream_index, int64_t ts, int flags)
{
    PMPContext *pmp = s->priv_data;
    pmp->cur_stream = 0;
    // fall back on default seek now
    return -1;
}