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
struct TYPE_4__ {int /*<<< orphan*/  conn_control; } ;
typedef  TYPE_1__ FTPContext ;

/* Variables and functions */
 int /*<<< orphan*/  ffurl_closep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftp_close_data_connection (TYPE_1__*) ; 

__attribute__((used)) static void ftp_close_both_connections(FTPContext *s)
{
    ffurl_closep(&s->conn_control);
    ftp_close_data_connection(s);
}