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
typedef  scalar_t__ apr_uint64_t ;
typedef  scalar_t__ apr_status_t ;
typedef  scalar_t__ apr_ssize_t ;
typedef  int apr_size_t ;
struct TYPE_4__ {int direction; scalar_t__ bufpos; scalar_t__ dataRead; int ungetchar; scalar_t__ buffer; int filePtr; int /*<<< orphan*/  eof_hit; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  filedes; } ;
typedef  TYPE_1__ apr_file_t ;

/* Variables and functions */
 scalar_t__ APR_EOF ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_file_flush_locked (TYPE_1__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 
 int read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t file_read_buffered(apr_file_t *thefile, void *buf,
                                       apr_size_t *nbytes)
{
    apr_ssize_t rv;
    char *pos = (char *)buf;
    apr_uint64_t blocksize;
    apr_uint64_t size = *nbytes;

    if (thefile->direction == 1) {
        rv = apr_file_flush_locked(thefile);
        if (rv) {
            return rv;
        }
        thefile->bufpos = 0;
        thefile->direction = 0;
        thefile->dataRead = 0;
    }

    rv = 0;
    if (thefile->ungetchar != -1) {
        *pos = (char)thefile->ungetchar;
        ++pos;
        --size;
        thefile->ungetchar = -1;
    }
    while (rv == 0 && size > 0) {
        if (thefile->bufpos >= thefile->dataRead) {
            int bytesread = read(thefile->filedes, thefile->buffer, 
                                 thefile->bufsize);
            if (bytesread == 0) {
                thefile->eof_hit = TRUE;
                rv = APR_EOF;
                break;
            }
            else if (bytesread == -1) {
                rv = errno;
                break;
            }
            thefile->dataRead = bytesread;
            thefile->filePtr += thefile->dataRead;
            thefile->bufpos = 0;
        }

        blocksize = size > thefile->dataRead - thefile->bufpos ? thefile->dataRead - thefile->bufpos : size;
        memcpy(pos, thefile->buffer + thefile->bufpos, blocksize);
        thefile->bufpos += blocksize;
        pos += blocksize;
        size -= blocksize;
    }

    *nbytes = pos - (char *)buf;
    if (*nbytes) {
        rv = 0;
    }
    return rv;
}