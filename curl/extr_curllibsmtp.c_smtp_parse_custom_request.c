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
struct connectdata {struct Curl_easy* data; } ;
struct SMTP {int /*<<< orphan*/  custom; } ;
struct TYPE_4__ {char** str; } ;
struct TYPE_3__ {struct SMTP* protop; } ;
struct Curl_easy {TYPE_2__ set; TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_urldecode (struct Curl_easy*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t STRING_CUSTOMREQUEST ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static CURLcode smtp_parse_custom_request(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct SMTP *smtp = data->req.protop;
  const char *custom = data->set.str[STRING_CUSTOMREQUEST];

  /* URL decode the custom request */
  if(custom)
    result = Curl_urldecode(data, custom, 0, &smtp->custom, NULL, TRUE);

  return result;
}