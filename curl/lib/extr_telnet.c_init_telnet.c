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
struct connectdata {TYPE_1__* data; } ;
struct TELNET {void** subnegotiation; void** him_preferred; void** us_preferred; int /*<<< orphan*/  telrcv_state; } ;
struct TYPE_4__ {struct TELNET* protop; } ;
struct TYPE_3__ {TYPE_2__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURL_SB_CLEAR (struct TELNET*) ; 
 size_t CURL_TELOPT_BINARY ; 
 size_t CURL_TELOPT_ECHO ; 
 size_t CURL_TELOPT_NAWS ; 
 size_t CURL_TELOPT_SGA ; 
 int /*<<< orphan*/  CURL_TS_DATA ; 
 void* CURL_YES ; 
 struct TELNET* calloc (int,int) ; 

__attribute__((used)) static
CURLcode init_telnet(struct connectdata *conn)
{
  struct TELNET *tn;

  tn = calloc(1, sizeof(struct TELNET));
  if(!tn)
    return CURLE_OUT_OF_MEMORY;

  conn->data->req.protop = tn; /* make us known */

  tn->telrcv_state = CURL_TS_DATA;

  /* Init suboptions */
  CURL_SB_CLEAR(tn);

  /* Set the options we want by default */
  tn->us_preferred[CURL_TELOPT_SGA] = CURL_YES;
  tn->him_preferred[CURL_TELOPT_SGA] = CURL_YES;

  /* To be compliant with previous releases of libcurl
     we enable this option by default. This behaviour
         can be changed thanks to the "BINARY" option in
         CURLOPT_TELNETOPTIONS
  */
  tn->us_preferred[CURL_TELOPT_BINARY] = CURL_YES;
  tn->him_preferred[CURL_TELOPT_BINARY] = CURL_YES;

  /* We must allow the server to echo what we sent
         but it is not necessary to request the server
         to do so (it might forces the server to close
         the connection). Hence, we ignore ECHO in the
         negotiate function
  */
  tn->him_preferred[CURL_TELOPT_ECHO] = CURL_YES;

  /* Set the subnegotiation fields to send information
    just after negotiation passed (do/will)

     Default values are (0,0) initialized by calloc.
     According to the RFC1013 it is valid:
     A value equal to zero is acceptable for the width (or height),
         and means that no character width (or height) is being sent.
         In this case, the width (or height) that will be assumed by the
         Telnet server is operating system specific (it will probably be
         based upon the terminal type information that may have been sent
         using the TERMINAL TYPE Telnet option). */
  tn->subnegotiation[CURL_TELOPT_NAWS] = CURL_YES;
  return CURLE_OK;
}