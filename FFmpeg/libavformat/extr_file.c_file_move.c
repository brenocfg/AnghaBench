#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* filename; } ;
typedef  TYPE_1__ URLContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ rename (char const*,char const*) ; 

__attribute__((used)) static int file_move(URLContext *h_src, URLContext *h_dst)
{
    const char *filename_src = h_src->filename;
    const char *filename_dst = h_dst->filename;
    av_strstart(filename_src, "file:", &filename_src);
    av_strstart(filename_dst, "file:", &filename_dst);

    if (rename(filename_src, filename_dst) < 0)
        return AVERROR(errno);

    return 0;
}