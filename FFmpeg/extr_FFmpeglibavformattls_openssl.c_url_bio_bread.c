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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXIT ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/ * GET_BIO_DATA (int /*<<< orphan*/ *) ; 
 int ffurl_read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int url_bio_bread(BIO *b, char *buf, int len)
{
    URLContext *h = GET_BIO_DATA(b);
    int ret = ffurl_read(h, buf, len);
    if (ret >= 0)
        return ret;
    BIO_clear_retry_flags(b);
    if (ret == AVERROR(EAGAIN))
        BIO_set_retry_read(b);
    if (ret == AVERROR_EXIT)
        return 0;
    return -1;
}