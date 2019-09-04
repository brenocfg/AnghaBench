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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  URLContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int BLOCKSIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/ * av_memdup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int set_aes_arg(URLContext *h, uint8_t **buf, int *buf_len,
                       uint8_t *default_buf, int default_buf_len,
                       const char *desc)
{
    if (!*buf_len) {
        if (!default_buf_len) {
            av_log(h, AV_LOG_ERROR, "%s not set\n", desc);
            return AVERROR(EINVAL);
        } else if (default_buf_len != BLOCKSIZE) {
            av_log(h, AV_LOG_ERROR,
                   "invalid %s size (%d bytes, block size is %d)\n",
                   desc, default_buf_len, BLOCKSIZE);
            return AVERROR(EINVAL);
        }
        *buf = av_memdup(default_buf, default_buf_len);
        if (!*buf)
            return AVERROR(ENOMEM);
        *buf_len = default_buf_len;
    } else if (*buf_len != BLOCKSIZE) {
        av_log(h, AV_LOG_ERROR,
               "invalid %s size (%d bytes, block size is %d)\n",
               desc, *buf_len, BLOCKSIZE);
        return AVERROR(EINVAL);
    }
    return 0;
}