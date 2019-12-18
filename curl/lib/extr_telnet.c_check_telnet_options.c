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
struct curl_slist {char* data; struct curl_slist* next; } ;
struct TYPE_5__ {scalar_t__ user_passwd; } ;
struct connectdata {int /*<<< orphan*/  user; TYPE_2__ bits; struct Curl_easy* data; } ;
struct TELNET {char subopt_wsx; char subopt_wsy; struct curl_slist* telnet_vars; void** him_preferred; void** us_preferred; scalar_t__* subopt_xdisploc; scalar_t__* subopt_ttype; } ;
struct TYPE_6__ {struct curl_slist* telnet_options; } ;
struct TYPE_4__ {scalar_t__ protop; } ;
struct Curl_easy {TYPE_3__ set; TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  option_arg ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_TELNET_OPTION_SYNTAX ; 
 scalar_t__ CURLE_UNKNOWN_OPTION ; 
 void* CURL_NO ; 
 size_t CURL_TELOPT_BINARY ; 
 size_t CURL_TELOPT_NAWS ; 
 size_t CURL_TELOPT_NEW_ENVIRON ; 
 size_t CURL_TELOPT_TTYPE ; 
 size_t CURL_TELOPT_XDISPLOC ; 
 void* CURL_YES ; 
 int atoi (char*) ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,char*) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,char*,char*) ; 
 scalar_t__ strcasecompare (char*,char*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char*,int) ; 

__attribute__((used)) static CURLcode check_telnet_options(struct connectdata *conn)
{
  struct curl_slist *head;
  struct curl_slist *beg;
  char option_keyword[128] = "";
  char option_arg[256] = "";
  struct Curl_easy *data = conn->data;
  struct TELNET *tn = (struct TELNET *)conn->data->req.protop;
  CURLcode result = CURLE_OK;
  int binary_option;

  /* Add the user name as an environment variable if it
     was given on the command line */
  if(conn->bits.user_passwd) {
    msnprintf(option_arg, sizeof(option_arg), "USER,%s", conn->user);
    beg = curl_slist_append(tn->telnet_vars, option_arg);
    if(!beg) {
      curl_slist_free_all(tn->telnet_vars);
      tn->telnet_vars = NULL;
      return CURLE_OUT_OF_MEMORY;
    }
    tn->telnet_vars = beg;
    tn->us_preferred[CURL_TELOPT_NEW_ENVIRON] = CURL_YES;
  }

  for(head = data->set.telnet_options; head; head = head->next) {
    if(sscanf(head->data, "%127[^= ]%*[ =]%255s",
              option_keyword, option_arg) == 2) {

      /* Terminal type */
      if(strcasecompare(option_keyword, "TTYPE")) {
        strncpy(tn->subopt_ttype, option_arg, 31);
        tn->subopt_ttype[31] = 0; /* String termination */
        tn->us_preferred[CURL_TELOPT_TTYPE] = CURL_YES;
        continue;
      }

      /* Display variable */
      if(strcasecompare(option_keyword, "XDISPLOC")) {
        strncpy(tn->subopt_xdisploc, option_arg, 127);
        tn->subopt_xdisploc[127] = 0; /* String termination */
        tn->us_preferred[CURL_TELOPT_XDISPLOC] = CURL_YES;
        continue;
      }

      /* Environment variable */
      if(strcasecompare(option_keyword, "NEW_ENV")) {
        beg = curl_slist_append(tn->telnet_vars, option_arg);
        if(!beg) {
          result = CURLE_OUT_OF_MEMORY;
          break;
        }
        tn->telnet_vars = beg;
        tn->us_preferred[CURL_TELOPT_NEW_ENVIRON] = CURL_YES;
        continue;
      }

      /* Window Size */
      if(strcasecompare(option_keyword, "WS")) {
        if(sscanf(option_arg, "%hu%*[xX]%hu",
                  &tn->subopt_wsx, &tn->subopt_wsy) == 2)
          tn->us_preferred[CURL_TELOPT_NAWS] = CURL_YES;
        else {
          failf(data, "Syntax error in telnet option: %s", head->data);
          result = CURLE_TELNET_OPTION_SYNTAX;
          break;
        }
        continue;
      }

      /* To take care or not of the 8th bit in data exchange */
      if(strcasecompare(option_keyword, "BINARY")) {
        binary_option = atoi(option_arg);
        if(binary_option != 1) {
          tn->us_preferred[CURL_TELOPT_BINARY] = CURL_NO;
          tn->him_preferred[CURL_TELOPT_BINARY] = CURL_NO;
        }
        continue;
      }

      failf(data, "Unknown telnet option %s", head->data);
      result = CURLE_UNKNOWN_OPTION;
      break;
    }
    failf(data, "Syntax error in telnet option: %s", head->data);
    result = CURLE_TELNET_OPTION_SYNTAX;
    break;
  }

  if(result) {
    curl_slist_free_all(tn->telnet_vars);
    tn->telnet_vars = NULL;
  }

  return result;
}