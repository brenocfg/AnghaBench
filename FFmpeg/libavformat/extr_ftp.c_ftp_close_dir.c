#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  conn_data; int /*<<< orphan*/  conn_control; int /*<<< orphan*/  dir_buffer; } ;
typedef  TYPE_2__ FTPContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_closep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftp_close_dir(URLContext *h)
{
    FTPContext *s = h->priv_data;
    av_freep(&s->dir_buffer);
    ffurl_closep(&s->conn_control);
    ffurl_closep(&s->conn_data);
    return 0;
}