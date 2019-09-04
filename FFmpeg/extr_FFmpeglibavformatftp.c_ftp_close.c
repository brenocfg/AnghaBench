#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {int /*<<< orphan*/  features; int /*<<< orphan*/  path; int /*<<< orphan*/  hostname; int /*<<< orphan*/  password; int /*<<< orphan*/  user; } ;
typedef  TYPE_2__ FTPContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ftp_close_both_connections (TYPE_2__*) ; 

__attribute__((used)) static int ftp_close(URLContext *h)
{
    FTPContext *s = h->priv_data;

    ff_dlog(h, "ftp protocol close\n");

    ftp_close_both_connections(s);
    av_freep(&s->user);
    av_freep(&s->password);
    av_freep(&s->hostname);
    av_freep(&s->path);
    av_freep(&s->features);

    return 0;
}