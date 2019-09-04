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

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  av_strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static int parse_content_encoding(URLContext *h, const char *p)
{
    if (!av_strncasecmp(p, "gzip", 4) ||
        !av_strncasecmp(p, "deflate", 7)) {
#if CONFIG_ZLIB
        HTTPContext *s = h->priv_data;

        s->compressed = 1;
        inflateEnd(&s->inflate_stream);
        if (inflateInit2(&s->inflate_stream, 32 + 15) != Z_OK) {
            av_log(h, AV_LOG_WARNING, "Error during zlib initialisation: %s\n",
                   s->inflate_stream.msg);
            return AVERROR(ENOSYS);
        }
        if (zlibCompileFlags() & (1 << 17)) {
            av_log(h, AV_LOG_WARNING,
                   "Your zlib was compiled without gzip support.\n");
            return AVERROR(ENOSYS);
        }
#else
        av_log(h, AV_LOG_WARNING,
               "Compressed (%s) content, need zlib with gzip support\n", p);
        return AVERROR(ENOSYS);
#endif /* CONFIG_ZLIB */
    } else if (!av_strncasecmp(p, "identity", 8)) {
        // The normal, no-encoding case (although servers shouldn't include
        // the header at all if this is the case).
    } else {
        av_log(h, AV_LOG_WARNING, "Unknown content coding: %s\n", p);
    }
    return 0;
}