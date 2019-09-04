#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct TYPE_8__ {int timeout; int fd; TYPE_1__ addr; scalar_t__ listen; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ UnixContext ;
struct TYPE_9__ {int rw_timeout; TYPE_2__* priv_data; } ;
typedef  TYPE_3__ URLContext ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ AVUNERROR (int) ; 
 scalar_t__ EADDRINUSE ; 
 int /*<<< orphan*/  av_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int ff_listen_bind (int,struct sockaddr*,int,int,TYPE_3__*) ; 
 int ff_listen_connect (int,struct sockaddr*,int,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_neterrno () ; 
 int ff_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unix_open(URLContext *h, const char *filename, int flags)
{
    UnixContext *s = h->priv_data;
    int fd, ret;

    av_strstart(filename, "unix:", &filename);
    s->addr.sun_family = AF_UNIX;
    av_strlcpy(s->addr.sun_path, filename, sizeof(s->addr.sun_path));

    if ((fd = ff_socket(AF_UNIX, s->type, 0)) < 0)
        return ff_neterrno();

    if (s->timeout < 0 && h->rw_timeout)
        s->timeout = h->rw_timeout / 1000;

    if (s->listen) {
        ret = ff_listen_bind(fd, (struct sockaddr *)&s->addr,
                             sizeof(s->addr), s->timeout, h);
        if (ret < 0)
            goto fail;
        fd = ret;
    } else {
        ret = ff_listen_connect(fd, (struct sockaddr *)&s->addr,
                                sizeof(s->addr), s->timeout, h, 0);
        if (ret < 0)
            goto fail;
    }

    s->fd = fd;

    return 0;

fail:
    if (s->listen && AVUNERROR(ret) != EADDRINUSE)
        unlink(s->addr.sun_path);
    if (fd >= 0)
        closesocket(fd);
    return ret;
}