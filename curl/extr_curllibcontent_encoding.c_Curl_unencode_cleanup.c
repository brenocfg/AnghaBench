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
struct connectdata {struct Curl_easy* data; } ;
struct SingleRequest {TYPE_2__* writer_stack; } ;
struct Curl_easy {struct SingleRequest req; } ;
struct TYPE_6__ {TYPE_1__* handler; struct TYPE_6__* downstream; } ;
typedef  TYPE_2__ contenc_writer ;
struct TYPE_5__ {int /*<<< orphan*/  (* close_writer ) (struct connectdata*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct connectdata*,TYPE_2__*) ; 

void Curl_unencode_cleanup(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  struct SingleRequest *k = &data->req;
  contenc_writer *writer = k->writer_stack;

  while(writer) {
    k->writer_stack = writer->downstream;
    writer->handler->close_writer(conn, writer);
    free(writer);
    writer = k->writer_stack;
  }
}