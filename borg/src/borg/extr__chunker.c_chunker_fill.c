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
typedef  scalar_t__ ssize_t ;
typedef  int off_t ;
struct TYPE_3__ {int last; int position; int remaining; scalar_t__ buf_size; int eof; scalar_t__ fh; int bytes_read; int /*<<< orphan*/  data; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  PyThreadState ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Chunker ;

/* Variables and functions */
 int /*<<< orphan*/  POSIX_FADV_DONTNEED ; 
 int /*<<< orphan*/  PyBytes_AsString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyBytes_Size (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetFromErrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyEval_RestoreThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyEval_SaveThread () ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 int /*<<< orphan*/ * PyObject_CallMethod (int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int getpagesize () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pagemask ; 
 int /*<<< orphan*/  posix_fadvise (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ read (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
chunker_fill(Chunker *c)
{
    ssize_t n;
    off_t offset, length;
    int overshoot;
    PyObject *data;
    PyThreadState *thread_state;

    memmove(c->data, c->data + c->last, c->position + c->remaining - c->last);
    c->position -= c->last;
    c->last = 0;
    n = c->buf_size - c->position - c->remaining;
    if(c->eof || n == 0) {
        return 1;
    }
    if(c->fh >= 0) {
        thread_state = PyEval_SaveThread();

        offset = c->bytes_read;
        // if we have a os-level file descriptor, use os-level API
        n = read(c->fh, c->data + c->position + c->remaining, n);
        if(n > 0) {
            c->remaining += n;
            c->bytes_read += n;
        }
        else
        if(n == 0) {
            c->eof = 1;
        }
        else {
            PyEval_RestoreThread(thread_state);
            // some error happened
            PyErr_SetFromErrno(PyExc_OSError);
            return 0;
        }
        length = c->bytes_read - offset;
        #if ( ( _XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L ) && defined(POSIX_FADV_DONTNEED) )

        // Only do it once per run.
        if (pagemask == 0)
            pagemask = getpagesize() - 1;

        // We tell the OS that we do not need the data that we just have read any
        // more (that it maybe has in the cache). This avoids that we spoil the
        // complete cache with data that we only read once and (due to cache
        // size limit) kick out data from the cache that might be still useful
        // for the OS or other processes.
        // We rollback the initial offset back to the start of the page,
        // to avoid it not being truncated as a partial page request.
        if (length > 0) {
            // All Linux kernels (at least up to and including 4.6(.0)) have a bug where
            // they truncate last partial page of POSIX_FADV_DONTNEED request, so we need
            // to page-align it ourselves. We'll need the rest of this page on the next
            // read (assuming this was not EOF).
            overshoot = (offset + length) & pagemask;
        } else {
            // For length == 0 we set overshoot 0, so the below
            // length - overshoot is 0, which means till end of file for
            // fadvise. This will cancel the final page and is not part
            // of the above workaround.
            overshoot = 0;
        }

        posix_fadvise(c->fh, offset & ~pagemask, length - overshoot, POSIX_FADV_DONTNEED);
        #endif

        PyEval_RestoreThread(thread_state);
    }
    else {
        // no os-level file descriptor, use Python file object API
        data = PyObject_CallMethod(c->fd, "read", "i", n);
        if(!data) {
            return 0;
        }
        n = PyBytes_Size(data);
        if(PyErr_Occurred()) {
            // we wanted bytes(), but got something else
            return 0;
        }
        if(n) {
            memcpy(c->data + c->position + c->remaining, PyBytes_AsString(data), n);
            c->remaining += n;
            c->bytes_read += n;
        }
        else {
            c->eof = 1;
        }
        Py_DECREF(data);
    }
    return 1;
}