#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int known_filesize; } ;
struct TYPE_16__ {TYPE_7__ ftpc; } ;
struct TYPE_13__ {void* type_set; } ;
struct TYPE_12__ {int /*<<< orphan*/ * rawalloc; } ;
struct connectdata {TYPE_8__ proto; int /*<<< orphan*/  passwd; int /*<<< orphan*/  user; TYPE_5__ bits; TYPE_4__ host; struct Curl_easy* data; } ;
struct FTP {int /*<<< orphan*/  passwd; int /*<<< orphan*/  user; scalar_t__ downloadsize; int /*<<< orphan*/  transfer; int /*<<< orphan*/ * path; } ;
struct TYPE_14__ {void* prefer_ascii; void* ftp_list_only; } ;
struct TYPE_10__ {int /*<<< orphan*/ * path; } ;
struct TYPE_11__ {TYPE_2__ up; } ;
struct TYPE_9__ {struct FTP* protop; } ;
struct Curl_easy {TYPE_6__ set; TYPE_3__ state; TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 char Curl_raw_toupper (char) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FTPTRANSFER_BODY ; 
 void* TRUE ; 
 struct FTP* calloc (int,int) ; 
 scalar_t__ isBadFtpString (int /*<<< orphan*/ ) ; 
 char* strstr (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static CURLcode ftp_setup_connection(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  char *type;
  struct FTP *ftp;

  conn->data->req.protop = ftp = calloc(sizeof(struct FTP), 1);
  if(NULL == ftp)
    return CURLE_OUT_OF_MEMORY;

  ftp->path = &data->state.up.path[1]; /* don't include the initial slash */

  /* FTP URLs support an extension like ";type=<typecode>" that
   * we'll try to get now! */
  type = strstr(ftp->path, ";type=");

  if(!type)
    type = strstr(conn->host.rawalloc, ";type=");

  if(type) {
    char command;
    *type = 0;                     /* it was in the middle of the hostname */
    command = Curl_raw_toupper(type[6]);
    conn->bits.type_set = TRUE;

    switch(command) {
    case 'A': /* ASCII mode */
      data->set.prefer_ascii = TRUE;
      break;

    case 'D': /* directory mode */
      data->set.ftp_list_only = TRUE;
      break;

    case 'I': /* binary mode */
    default:
      /* switch off ASCII */
      data->set.prefer_ascii = FALSE;
      break;
    }
  }

  /* get some initial data into the ftp struct */
  ftp->transfer = FTPTRANSFER_BODY;
  ftp->downloadsize = 0;

  /* No need to duplicate user+password, the connectdata struct won't change
     during a session, but we re-init them here since on subsequent inits
     since the conn struct may have changed or been replaced.
  */
  ftp->user = conn->user;
  ftp->passwd = conn->passwd;
  if(isBadFtpString(ftp->user))
    return CURLE_URL_MALFORMAT;
  if(isBadFtpString(ftp->passwd))
    return CURLE_URL_MALFORMAT;

  conn->proto.ftpc.known_filesize = -1; /* unknown size for now */

  return CURLE_OK;
}