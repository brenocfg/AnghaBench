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
struct TYPE_4__ {int /*<<< orphan*/  resetprefs; } ;
struct smtp_conn {TYPE_2__ sasl; } ;
struct TYPE_3__ {struct smtp_conn smtpc; } ;
struct connectdata {char* options; TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  Curl_sasl_parse_url_auth_option (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strncasecompare (char const*,char*,int) ; 

__attribute__((used)) static CURLcode smtp_parse_url_options(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  const char *ptr = conn->options;

  smtpc->sasl.resetprefs = TRUE;

  while(!result && ptr && *ptr) {
    const char *key = ptr;
    const char *value;

    while(*ptr && *ptr != '=')
      ptr++;

    value = ptr + 1;

    while(*ptr && *ptr != ';')
      ptr++;

    if(strncasecompare(key, "AUTH=", 5))
      result = Curl_sasl_parse_url_auth_option(&smtpc->sasl,
                                               value, ptr - value);
    else
      result = CURLE_URL_MALFORMAT;

    if(*ptr == ';')
      ptr++;
  }

  return result;
}