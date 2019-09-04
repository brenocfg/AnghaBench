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
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int ffio_fdopen (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_close (int /*<<< orphan*/ *) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ *) ; 

int ffio_open_whitelist(AVIOContext **s, const char *filename, int flags,
                         const AVIOInterruptCB *int_cb, AVDictionary **options,
                         const char *whitelist, const char *blacklist
                        )
{
    URLContext *h;
    int err;

    err = ffurl_open_whitelist(&h, filename, flags, int_cb, options, whitelist, blacklist, NULL);
    if (err < 0)
        return err;
    err = ffio_fdopen(s, h);
    if (err < 0) {
        ffurl_close(h);
        return err;
    }
    return 0;
}