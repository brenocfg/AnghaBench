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
typedef  long timediff_t ;
struct prunedead {int /*<<< orphan*/ * extracted; struct Curl_easy* data; } ;
struct curltime {int dummy; } ;
struct TYPE_3__ {TYPE_2__* conn_cache; } ;
struct Curl_easy {TYPE_1__ state; } ;
struct TYPE_4__ {struct curltime last_cleanup; } ;

/* Variables and functions */
 scalar_t__ Curl_conncache_foreach (struct Curl_easy*,TYPE_2__*,struct prunedead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_disconnect (struct Curl_easy*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct curltime Curl_now () ; 
 long Curl_timediff (struct curltime,struct curltime) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  call_extract_if_dead ; 

__attribute__((used)) static void prune_dead_connections(struct Curl_easy *data)
{
  struct curltime now = Curl_now();
  timediff_t elapsed =
    Curl_timediff(now, data->state.conn_cache->last_cleanup);

  if(elapsed >= 1000L) {
    struct prunedead prune;
    prune.data = data;
    prune.extracted = NULL;
    while(Curl_conncache_foreach(data, data->state.conn_cache, &prune,
                                 call_extract_if_dead)) {
      /* disconnect it */
      (void)Curl_disconnect(data, prune.extracted, /* dead_connection */TRUE);
    }
    data->state.conn_cache->last_cleanup = now;
  }
}