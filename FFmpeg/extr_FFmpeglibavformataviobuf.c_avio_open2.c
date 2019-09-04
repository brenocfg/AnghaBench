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
typedef  int /*<<< orphan*/  AVIOInterruptCB ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int ffio_open_whitelist (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int avio_open2(AVIOContext **s, const char *filename, int flags,
               const AVIOInterruptCB *int_cb, AVDictionary **options)
{
    return ffio_open_whitelist(s, filename, flags, int_cb, options, NULL, NULL);
}