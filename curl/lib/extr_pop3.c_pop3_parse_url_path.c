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
struct connectdata {struct Curl_easy* data; } ;
struct POP3 {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {char* path; } ;
struct TYPE_6__ {TYPE_2__ up; } ;
struct TYPE_4__ {struct POP3* protop; } ;
struct Curl_easy {TYPE_3__ state; TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_urldecode (struct Curl_easy*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static CURLcode pop3_parse_url_path(struct connectdata *conn)
{
  /* The POP3 struct is already initialised in pop3_connect() */
  struct Curl_easy *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  const char *path = &data->state.up.path[1]; /* skip leading path */

  /* URL decode the path for the message ID */
  return Curl_urldecode(data, path, 0, &pop3->id, NULL, TRUE);
}