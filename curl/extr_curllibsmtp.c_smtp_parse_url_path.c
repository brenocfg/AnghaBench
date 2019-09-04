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
struct smtp_conn {int /*<<< orphan*/  domain; } ;
struct TYPE_4__ {struct smtp_conn smtpc; } ;
struct connectdata {struct Curl_easy* data; TYPE_1__ proto; } ;
struct TYPE_6__ {char* path; } ;
struct TYPE_5__ {TYPE_3__ up; } ;
struct Curl_easy {TYPE_2__ state; } ;
typedef  int /*<<< orphan*/  localhost ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_gethostname (char*,int) ; 
 int /*<<< orphan*/  Curl_urldecode (struct Curl_easy*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOSTNAME_MAX ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static CURLcode smtp_parse_url_path(struct connectdata *conn)
{
  /* The SMTP struct is already initialised in smtp_connect() */
  struct Curl_easy *data = conn->data;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  const char *path = &data->state.up.path[1]; /* skip leading path */
  char localhost[HOSTNAME_MAX + 1];

  /* Calculate the path if necessary */
  if(!*path) {
    if(!Curl_gethostname(localhost, sizeof(localhost)))
      path = localhost;
    else
      path = "localhost";
  }

  /* URL decode the path and use it as the domain in our EHLO */
  return Curl_urldecode(conn->data, path, 0, &smtpc->domain, NULL, TRUE);
}