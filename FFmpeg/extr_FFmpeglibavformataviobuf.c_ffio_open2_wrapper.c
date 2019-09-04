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
struct AVFormatContext {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; } ;
typedef  int /*<<< orphan*/  AVIOInterruptCB ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int ffio_open_whitelist (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ffio_open2_wrapper(struct AVFormatContext *s, AVIOContext **pb, const char *url, int flags,
                       const AVIOInterruptCB *int_cb, AVDictionary **options)
{
    return ffio_open_whitelist(pb, url, flags, int_cb, options, s->protocol_whitelist, s->protocol_blacklist);
}