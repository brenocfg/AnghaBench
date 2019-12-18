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
struct stat {int st_mode; } ;
struct TYPE_3__ {char* filename; } ;
typedef  TYPE_1__ URLContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_FLAG_READ ; 
 int AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  R_OK ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  errno ; 
 int stat (char const*,struct stat*) ; 
 int win32_stat (char const*,struct stat*) ; 

__attribute__((used)) static int file_check(URLContext *h, int mask)
{
    int ret = 0;
    const char *filename = h->filename;
    av_strstart(filename, "file:", &filename);

    {
#if HAVE_ACCESS && defined(R_OK)
    if (access(filename, F_OK) < 0)
        return AVERROR(errno);
    if (mask&AVIO_FLAG_READ)
        if (access(filename, R_OK) >= 0)
            ret |= AVIO_FLAG_READ;
    if (mask&AVIO_FLAG_WRITE)
        if (access(filename, W_OK) >= 0)
            ret |= AVIO_FLAG_WRITE;
#else
    struct stat st;
#   ifndef _WIN32
    ret = stat(filename, &st);
#   else
    ret = win32_stat(filename, &st);
#   endif
    if (ret < 0)
        return AVERROR(errno);

    ret |= st.st_mode&S_IRUSR ? mask&AVIO_FLAG_READ  : 0;
    ret |= st.st_mode&S_IWUSR ? mask&AVIO_FLAG_WRITE : 0;
#endif
    }
    return ret;
}