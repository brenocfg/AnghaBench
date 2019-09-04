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
struct auth {int dummy; } ;
struct UserDefined {int dummy; } ;
struct Progress {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int current_speed; TYPE_2__ authproxy; TYPE_2__ authhost; } ;
struct Curl_easy {TYPE_1__ state; TYPE_2__ progress; TYPE_2__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_digest_cleanup (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_free_request_state (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_freeset (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_init_userdefined (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_initinfo (struct Curl_easy*) ; 
 int /*<<< orphan*/  PGRS_HIDE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void curl_easy_reset(struct Curl_easy *data)
{
  Curl_free_request_state(data);

  /* zero out UserDefined data: */
  Curl_freeset(data);
  memset(&data->set, 0, sizeof(struct UserDefined));
  (void)Curl_init_userdefined(data);

  /* zero out Progress data: */
  memset(&data->progress, 0, sizeof(struct Progress));

  /* zero out PureInfo data: */
  Curl_initinfo(data);

  data->progress.flags |= PGRS_HIDE;
  data->state.current_speed = -1; /* init to negative == impossible */

  /* zero out authentication data: */
  memset(&data->state.authhost, 0, sizeof(struct auth));
  memset(&data->state.authproxy, 0, sizeof(struct auth));
  Curl_digest_cleanup(data);
}