#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  upload_method; } ;
struct connection {int rdbuf_pos; TYPE_1__ info; int /*<<< orphan*/  rdbuf; } ;

/* Variables and functions */
 char* TOKEN_RESPONSE ; 
 int /*<<< orphan*/  UPLOAD_ECHO ; 
 int /*<<< orphan*/  UPLOAD_TFTP ; 
 int /*<<< orphan*/  UPLOAD_WGET ; 
 int strlen (char*) ; 
 int util_memsearch (int /*<<< orphan*/ ,int,char*,int) ; 

int connection_consume_upload_methods(struct connection *conn)
{
    int offset = util_memsearch(conn->rdbuf, conn->rdbuf_pos, TOKEN_RESPONSE, strlen(TOKEN_RESPONSE));

    if (offset == -1)
        return 0;

    if (util_memsearch(conn->rdbuf, offset, "wget: applet not found", 22) == -1)
        conn->info.upload_method = UPLOAD_WGET;
    else if (util_memsearch(conn->rdbuf, offset, "tftp: applet not found", 22) == -1)
        conn->info.upload_method = UPLOAD_TFTP;
    else
        conn->info.upload_method = UPLOAD_ECHO;

    return offset;
}