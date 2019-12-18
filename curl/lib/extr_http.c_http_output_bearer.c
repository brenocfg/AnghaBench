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
struct TYPE_2__ {char* userpwd; } ;
struct connectdata {int /*<<< orphan*/  oauth_bearer; TYPE_1__ allocptr; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 char* aprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static CURLcode http_output_bearer(struct connectdata *conn)
{
  char **userp;
  CURLcode result = CURLE_OK;

  userp = &conn->allocptr.userpwd;
  free(*userp);
  *userp = aprintf("Authorization: Bearer %s\r\n",
                   conn->oauth_bearer);

  if(!*userp) {
    result = CURLE_OUT_OF_MEMORY;
    goto fail;
  }

  fail:
  return result;
}