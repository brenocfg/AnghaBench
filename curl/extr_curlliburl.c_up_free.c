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
struct urlpieces {int /*<<< orphan*/  query; int /*<<< orphan*/  path; int /*<<< orphan*/  options; int /*<<< orphan*/  password; int /*<<< orphan*/  user; int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; int /*<<< orphan*/  scheme; } ;
struct TYPE_2__ {int /*<<< orphan*/ * uh; struct urlpieces up; } ;
struct Curl_easy {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_url_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void up_free(struct Curl_easy *data)
{
  struct urlpieces *up = &data->state.up;
  Curl_safefree(up->scheme);
  Curl_safefree(up->hostname);
  Curl_safefree(up->port);
  Curl_safefree(up->user);
  Curl_safefree(up->password);
  Curl_safefree(up->options);
  Curl_safefree(up->path);
  Curl_safefree(up->query);
  curl_url_cleanup(data->state.uh);
  data->state.uh = NULL;
}