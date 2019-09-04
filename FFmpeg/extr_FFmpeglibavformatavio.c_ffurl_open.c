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
typedef  int /*<<< orphan*/  URLContext ;
typedef  int /*<<< orphan*/  AVIOInterruptCB ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int ffurl_open_whitelist (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ffurl_open(URLContext **puc, const char *filename, int flags,
               const AVIOInterruptCB *int_cb, AVDictionary **options)
{
    return ffurl_open_whitelist(puc, filename, flags,
                                int_cb, options, NULL, NULL, NULL);
}