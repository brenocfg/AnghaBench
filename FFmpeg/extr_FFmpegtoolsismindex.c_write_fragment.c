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
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int avio_open2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int copy_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int write_fragment(const char *filename, AVIOContext *in)
{
    AVIOContext *out = NULL;
    int ret;

    if ((ret = avio_open2(&out, filename, AVIO_FLAG_WRITE, NULL, NULL)) < 0) {
        char errbuf[100];
        av_strerror(ret, errbuf, sizeof(errbuf));
        fprintf(stderr, "Unable to open %s: %s\n", filename, errbuf);
        return ret;
    }
    ret = copy_tag(in, out, MKBETAG('m', 'o', 'o', 'f'));
    if (!ret)
        ret = copy_tag(in, out, MKBETAG('m', 'd', 'a', 't'));

    avio_flush(out);
    avio_close(out);

    return ret;
}