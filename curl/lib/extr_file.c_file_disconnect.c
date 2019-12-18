#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connectdata {TYPE_2__* data; } ;
struct FILEPROTO {int fd; int /*<<< orphan*/ * path; int /*<<< orphan*/  freepath; } ;
struct TYPE_3__ {struct FILEPROTO* protop; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static CURLcode file_disconnect(struct connectdata *conn,
                                bool dead_connection)
{
  struct FILEPROTO *file = conn->data->req.protop;
  (void)dead_connection; /* not used */

  if(file) {
    Curl_safefree(file->freepath);
    file->path = NULL;
    if(file->fd != -1)
      close(file->fd);
    file->fd = -1;
  }

  return CURLE_OK;
}