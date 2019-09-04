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
struct MD5Context {int /*<<< orphan*/  md5; } ;
struct TYPE_3__ {struct MD5Context* priv_data; } ;
typedef  TYPE_1__ URLContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_md5_alloc () ; 
 int /*<<< orphan*/  av_md5_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int md5_open(URLContext *h, const char *filename, int flags)
{
    struct MD5Context *c = h->priv_data;

    if (!(flags & AVIO_FLAG_WRITE))
        return AVERROR(EINVAL);

    c->md5 = av_md5_alloc();
    if (!c->md5)
        return AVERROR(ENOMEM);
    av_md5_init(c->md5);

    return 0;
}