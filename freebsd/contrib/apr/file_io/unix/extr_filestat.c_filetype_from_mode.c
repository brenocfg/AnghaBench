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
typedef  int mode_t ;
typedef  int /*<<< orphan*/  apr_filetype_e ;

/* Variables and functions */
 int /*<<< orphan*/  APR_BLK ; 
 int /*<<< orphan*/  APR_CHR ; 
 int /*<<< orphan*/  APR_DIR ; 
 int /*<<< orphan*/  APR_LNK ; 
 int /*<<< orphan*/  APR_PIPE ; 
 int /*<<< orphan*/  APR_REG ; 
 int /*<<< orphan*/  APR_SOCK ; 
 int /*<<< orphan*/  APR_UNKFILE ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int /*<<< orphan*/  S_ISFIFO (int) ; 
 int /*<<< orphan*/  S_ISSOCK (int) ; 

__attribute__((used)) static apr_filetype_e filetype_from_mode(mode_t mode)
{
    apr_filetype_e type;

    switch (mode & S_IFMT) {
    case S_IFREG:
        type = APR_REG;  break;
    case S_IFDIR:
        type = APR_DIR;  break;
    case S_IFLNK:
        type = APR_LNK;  break;
    case S_IFCHR:
        type = APR_CHR;  break;
    case S_IFBLK:
        type = APR_BLK;  break;
#if defined(S_IFFIFO)
    case S_IFFIFO:
        type = APR_PIPE; break;
#endif
#if !defined(BEOS) && defined(S_IFSOCK)
    case S_IFSOCK:
        type = APR_SOCK; break;
#endif

    default:
	/* Work around missing S_IFxxx values above
         * for Linux et al.
         */
#if !defined(S_IFFIFO) && defined(S_ISFIFO)
    	if (S_ISFIFO(mode)) {
            type = APR_PIPE;
	} else
#endif
#if !defined(BEOS) && !defined(S_IFSOCK) && defined(S_ISSOCK)
    	if (S_ISSOCK(mode)) {
            type = APR_SOCK;
	} else
#endif
        type = APR_UNKFILE;
    }
    return type;
}