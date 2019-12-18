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
struct TYPE_5__ {TYPE_1__* probe; } ;
struct TYPE_6__ {TYPE_2__ doh; int /*<<< orphan*/  newurl; int /*<<< orphan*/  protop; } ;
struct Curl_easy {TYPE_3__ req; } ;
struct TYPE_4__ {int /*<<< orphan*/  easy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 

void Curl_free_request_state(struct Curl_easy *data)
{
  Curl_safefree(data->req.protop);
  Curl_safefree(data->req.newurl);

#ifndef CURL_DISABLE_DOH
  Curl_close(&data->req.doh.probe[0].easy);
  Curl_close(&data->req.doh.probe[1].easy);
#endif
}