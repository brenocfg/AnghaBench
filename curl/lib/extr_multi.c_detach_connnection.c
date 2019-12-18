#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connectdata {int /*<<< orphan*/  easyq; } ;
struct Curl_easy {struct connectdata* conn; int /*<<< orphan*/  conn_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void detach_connnection(struct Curl_easy *data)
{
  struct connectdata *conn = data->conn;
  if(conn)
    Curl_llist_remove(&conn->easyq, &data->conn_queue, NULL);
  data->conn = NULL;
}