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
typedef  int timediff_t ;
struct curltime {int dummy; } ;
struct connectdata {int /*<<< orphan*/  lastused; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int maxage_conn; } ;
struct Curl_easy {TYPE_1__ set; } ;

/* Variables and functions */
 int Curl_timediff (struct curltime,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int) ; 

__attribute__((used)) static bool conn_maxage(struct Curl_easy *data,
                        struct connectdata *conn,
                        struct curltime now)
{
  if(!conn->data) {
    timediff_t idletime = Curl_timediff(now, conn->lastused);
    idletime /= 1000; /* integer seconds is fine */

    if(idletime > data->set.maxage_conn) {
      infof(data, "Too old connection (%ld seconds), disconnect it\n",
            idletime);
      return TRUE;
    }
  }
  return FALSE;
}