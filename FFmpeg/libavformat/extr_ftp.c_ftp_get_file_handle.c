#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {scalar_t__ conn_data; } ;
typedef  TYPE_2__ FTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ff_dlog (TYPE_1__*,char*) ; 
 int ffurl_get_file_handle (scalar_t__) ; 

__attribute__((used)) static int ftp_get_file_handle(URLContext *h)
{
    FTPContext *s = h->priv_data;

    ff_dlog(h, "ftp protocol get_file_handle\n");

    if (s->conn_data)
        return ffurl_get_file_handle(s->conn_data);

    return AVERROR(EIO);
}