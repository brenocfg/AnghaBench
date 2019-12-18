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
struct TYPE_3__ {int member_1; void* member_2; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ FileLogContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 char* av_malloc (size_t) ; 
 char* av_strdup (void*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  file_log_ctx_class ; 
 int /*<<< orphan*/  free (void*) ; 
 int mkstemp (char*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 
 int strlen (char const*) ; 
 void* tempnam (char*,char const*) ; 

int avpriv_tempfile(const char *prefix, char **filename, int log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    int fd = -1;
#if !HAVE_MKSTEMP
    void *ptr= tempnam(NULL, prefix);
    if(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
#undef free
    free(ptr);
#else
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#endif
    /* -----common section-----*/
    if (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        return AVERROR(ENOMEM);
    }
#if !HAVE_MKSTEMP
#   ifndef O_BINARY
#       define O_BINARY 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_BINARY | O_CREAT | O_EXCL, 0600);
#else
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#if defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    if (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    if (fd < 0) {
        int err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        return err;
    }
    return fd; /* success */
}