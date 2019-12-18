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
struct connectdata {int /*<<< orphan*/  lastused; struct Curl_easy* data; } ;
struct Curl_easy {TYPE_1__* multi; } ;
struct TYPE_2__ {int maxconnects; int num_easy; } ;

/* Variables and functions */
 struct connectdata* Curl_conncache_extract_oldest (struct Curl_easy*) ; 
 size_t Curl_conncache_size (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_disconnect (struct Curl_easy*,struct connectdata*,int) ; 
 int /*<<< orphan*/  Curl_now () ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 

bool Curl_conncache_return_conn(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;

  /* data->multi->maxconnects can be negative, deal with it. */
  size_t maxconnects =
    (data->multi->maxconnects < 0) ? data->multi->num_easy * 4:
    data->multi->maxconnects;
  struct connectdata *conn_candidate = NULL;

  conn->data = NULL; /* no owner anymore */
  conn->lastused = Curl_now(); /* it was used up until now */
  if(maxconnects > 0 &&
     Curl_conncache_size(data) > maxconnects) {
    infof(data, "Connection cache is full, closing the oldest one.\n");

    conn_candidate = Curl_conncache_extract_oldest(data);
    if(conn_candidate) {
      /* the winner gets the honour of being disconnected */
      (void)Curl_disconnect(data, conn_candidate, /* dead_connection */ FALSE);
    }
  }

  return (conn_candidate == conn) ? FALSE : TRUE;

}