#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rawalloc; } ;
struct connectdata {TYPE_1__ host; int /*<<< orphan*/  transport; struct Curl_easy* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  prefer_ascii; } ;
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
struct TYPE_8__ {TYPE_3__ up; } ;
struct Curl_easy {TYPE_2__ set; TYPE_4__ state; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 char Curl_raw_toupper (char) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRNSPRT_UDP ; 
 int /*<<< orphan*/  TRUE ; 
 char* strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static CURLcode tftp_setup_connection(struct connectdata * conn)
{
  struct Curl_easy *data = conn->data;
  char *type;

  conn->transport = TRNSPRT_UDP;

  /* TFTP URLs support an extension like ";mode=<typecode>" that
   * we'll try to get now! */
  type = strstr(data->state.up.path, ";mode=");

  if(!type)
    type = strstr(conn->host.rawalloc, ";mode=");

  if(type) {
    char command;
    *type = 0;                   /* it was in the middle of the hostname */
    command = Curl_raw_toupper(type[6]);

    switch(command) {
    case 'A': /* ASCII mode */
    case 'N': /* NETASCII mode */
      data->set.prefer_ascii = TRUE;
      break;

    case 'O': /* octet mode */
    case 'I': /* binary mode */
    default:
      /* switch off ASCII */
      data->set.prefer_ascii = FALSE;
      break;
    }
  }

  return CURLE_OK;
}