#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ voidpf ;
typedef  scalar_t__ uInt ;
struct zipent {int compression_method; scalar_t__ compressed_size; scalar_t__ uncompressed_size; int version_needed_to_extract; int os_needed_to_extract; scalar_t__ disk_number_start; } ;
struct TYPE_9__ {int avail_in; int avail_out; int /*<<< orphan*/ * next_in; int /*<<< orphan*/ * next_out; scalar_t__ opaque; scalar_t__ zfree; scalar_t__ zalloc; } ;
struct TYPE_7__ {int z_err; int transparent; char mode; char* path; TYPE_5__ stream; int /*<<< orphan*/ * file; scalar_t__ start; int /*<<< orphan*/ * inbuf; int /*<<< orphan*/ * msg; int /*<<< orphan*/  crc; int /*<<< orphan*/  back; scalar_t__ out; scalar_t__ in; scalar_t__ z_eof; int /*<<< orphan*/ * outbuf; } ;
typedef  TYPE_1__ gz_stream ;
typedef  int /*<<< orphan*/ * gzFile ;
typedef  scalar_t__ free_func ;
typedef  scalar_t__ alloc_func ;
struct TYPE_8__ {char* zip; scalar_t__ number_of_this_disk; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_2__ ZIP ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ALLOC (int) ; 
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  ERROR_CORRUPT ; 
 int /*<<< orphan*/  ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  MAX_WBITS ; 
 int Z_BUFSIZE ; 
 int Z_ERRNO ; 
 int /*<<< orphan*/ * Z_NULL ; 
 int Z_OK ; 
 int /*<<< orphan*/  crc32 (long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * destroy (TYPE_1__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errormsg (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ftell (int /*<<< orphan*/ *) ; 
 int inflateInit2 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ seekcompresszip (TYPE_2__*,struct zipent*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

gzFile zip2gz(ZIP* zip, struct zipent* ent)
{
    int err;
    gz_stream *s;
    const char *path;
    int transparent = 0;
    uInt len;

    if (!zip || !ent)
        return NULL;

    /* zip stuff */
    if (ent->compression_method == 0x0000)
    {
        /* file is not compressed, simply stored */

        /* check if size are equal */
        if (ent->compressed_size != ent->uncompressed_size) {
            errormsg("Wrong uncompressed size in store compression", ERROR_CORRUPT,zip->zip);
            return NULL;
        }

        transparent = 1;
    }
    else if (ent->compression_method == 0x0008)
    {
        /* file is compressed using "Deflate" method */
        if (ent->version_needed_to_extract > 0x14) {
            errormsg("Version too new", ERROR_UNSUPPORTED,zip->zip);
            return NULL;
        }

        if (ent->os_needed_to_extract != 0x00) {
            errormsg("OS not supported", ERROR_UNSUPPORTED,zip->zip);
            return NULL;
        }

        if (ent->disk_number_start != zip->number_of_this_disk) {
            errormsg("Cannot span disks", ERROR_UNSUPPORTED,zip->zip);
            return NULL;
        }

    } else {
        errormsg("Compression method unsupported", ERROR_UNSUPPORTED, zip->zip);
        return NULL;
    }

    /* seek to compressed data */
    if (seekcompresszip(zip,ent) != 0) {
        return NULL;
    }

    path = zip->zip;

    /* normal gzip init for read */
    s = (gz_stream *)ALLOC(sizeof(gz_stream));
    if (!s) return Z_NULL;

    s->stream.zalloc = (alloc_func)0;
    s->stream.zfree = (free_func)0;
    s->stream.opaque = (voidpf)0;
    s->stream.next_in = s->inbuf = Z_NULL;
    s->stream.next_out = s->outbuf = Z_NULL;
    s->stream.avail_in = s->stream.avail_out = 0;
    s->file = NULL;
    s->z_err = Z_OK;
    s->z_eof = 0;
    s->in = 0;
    s->out = 0;
    s->back = EOF;
    s->crc = crc32(0L, Z_NULL, 0);
    s->msg = NULL;
    s->transparent = transparent;
    s->mode = 'r';

    s->path = (char*)ALLOC(strlen(path)+1);
    if (s->path == NULL) {
        return destroy(s), (gzFile)Z_NULL;
    }
    strcpy(s->path, path); /* do this early for debugging */

    s->stream.next_in  = s->inbuf = (Byte*)ALLOC(Z_BUFSIZE);

    err = inflateInit2(&(s->stream), -MAX_WBITS);
    /* windowBits is passed < 0 to tell that there is no zlib header.
     * Note that in this case inflate *requires* an extra "dummy" byte
     * after the compressed stream in order to complete decompression and
     * return Z_STREAM_END. Here the gzip CRC32 ensures that 4 bytes are
     * present after the compressed stream.
     */
    if (err != Z_OK || s->inbuf == Z_NULL) {
        return destroy(s), (gzFile)Z_NULL;
    }
    s->stream.avail_out = Z_BUFSIZE;

    errno = 0;
    s->file = zip->fp;
    if (s->file == NULL) {
        return destroy(s), (gzFile)Z_NULL;
    }

    /* check_header(s); */
    errno = 0;
    len = (uInt)fread(s->inbuf, 1, Z_BUFSIZE, s->file);
    if (len == 0 && ferror(s->file)) s->z_err = Z_ERRNO;
    s->stream.avail_in += len;
    s->stream.next_in = s->inbuf;
    if (s->stream.avail_in < 2) {
        return destroy(s), (gzFile)Z_NULL;
    }

    s->start = ftell(s->file) - s->stream.avail_in;

    return (gzFile)s;
}