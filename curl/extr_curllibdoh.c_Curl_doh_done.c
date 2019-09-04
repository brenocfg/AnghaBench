#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * headers; int /*<<< orphan*/  pending; } ;
struct TYPE_6__ {TYPE_2__ doh; } ;
struct TYPE_4__ {struct Curl_easy* dohfor; } ;
struct Curl_easy {TYPE_3__ req; TYPE_1__ set; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_expire (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPIRE_RUN_NOW ; 
 int /*<<< orphan*/  curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Curl_doh_done(struct Curl_easy *doh, CURLcode result)
{
  struct Curl_easy *data = doh->set.dohfor;
  /* so one of the DOH request done for the 'data' transfer is now complete! */
  data->req.doh.pending--;
  infof(data, "a DOH request is completed, %u to go\n", data->req.doh.pending);
  if(result)
    infof(data, "DOH request %s\n", curl_easy_strerror(result));

  if(!data->req.doh.pending) {
    /* DOH completed */
    curl_slist_free_all(data->req.doh.headers);
    data->req.doh.headers = NULL;
    Curl_expire(data, 0, EXPIRE_RUN_NOW);
  }
  return 0;
}