#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_12__ {int /*<<< orphan*/  utf8; } ;
struct TYPE_11__ {char* dir_buffer; int dir_buffer_offset; int dir_buffer_size; int /*<<< orphan*/  utf8; int /*<<< orphan*/  conn_data; } ;
typedef  TYPE_2__ FTPContext ;
typedef  TYPE_3__ AVIODirEntry ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int DIR_BUFFER_SIZE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  avio_free_directory_entry (TYPE_3__**) ; 
 TYPE_3__* ff_alloc_dir_entry () ; 
 int ffurl_read (int /*<<< orphan*/ ,char*,int) ; 
 int ftp_parse_entry (TYPE_1__*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int ftp_read_dir(URLContext *h, AVIODirEntry **next)
{
    FTPContext *s = h->priv_data;
    char *start, *found;
    int ret, retried;

    do {
        retried = 0;
        start = s->dir_buffer + s->dir_buffer_offset;
        while (!(found = strstr(start, "\n"))) {
            if (retried)
                return AVERROR(EIO);
            s->dir_buffer_size -= s->dir_buffer_offset;
            s->dir_buffer_offset = 0;
            if (s->dir_buffer_size)
                memmove(s->dir_buffer, start, s->dir_buffer_size);
            ret = ffurl_read(s->conn_data, s->dir_buffer + s->dir_buffer_size, DIR_BUFFER_SIZE - (s->dir_buffer_size + 1));
            if (ret < 0)
                return ret;
            if (!ret) {
                *next = NULL;
                return 0;
            }
            s->dir_buffer_size += ret;
            s->dir_buffer[s->dir_buffer_size] = 0;
            start = s->dir_buffer;
            retried = 1;
        }
        s->dir_buffer_offset += (found + 1 - start);
        found[0] = 0;
        if (found > start && found[-1] == '\r')
            found[-1] = 0;

        *next = ff_alloc_dir_entry();
        if (!*next)
            return AVERROR(ENOMEM);
        (*next)->utf8 = s->utf8;
        ret = ftp_parse_entry(h, start, *next);
        if (ret) {
            avio_free_directory_entry(next);
            if (ret < 0)
                return ret;
        }
    } while (ret > 0);
    return 0;
}