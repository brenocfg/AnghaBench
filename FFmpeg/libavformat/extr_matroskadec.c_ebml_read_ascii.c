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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int NEEDS_CHECKING ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_malloc (int) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ebml_read_ascii(AVIOContext *pb, int size, char **str)
{
    char *res;
    int ret;

    /* EBML strings are usually not 0-terminated, so we allocate one
     * byte more, read the string and NULL-terminate it ourselves. */
    if (!(res = av_malloc(size + 1)))
        return AVERROR(ENOMEM);
    if ((ret = avio_read(pb, (uint8_t *) res, size)) != size) {
        av_free(res);
        return ret < 0 ? ret : NEEDS_CHECKING;
    }
    (res)[size] = '\0';
    av_free(*str);
    *str = res;

    return 0;
}