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
struct TYPE_7__ {int /*<<< orphan*/  pp; } ;
struct TYPE_8__ {TYPE_3__ ftpc; } ;
struct connectdata {TYPE_4__ proto; struct Curl_easy* data; } ;
struct FTP {char* path; } ;
struct TYPE_6__ {scalar_t__ ftp_filemethod; char** str; scalar_t__ ftp_list_only; } ;
struct TYPE_5__ {struct FTP* protop; } ;
struct Curl_easy {TYPE_2__ set; TYPE_1__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ Curl_pp_sendf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ Curl_urldecode (struct Curl_easy*,char const*,size_t,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FTPFILE_NOCWD ; 
 int /*<<< orphan*/  FTP_LIST ; 
 size_t STRING_CUSTOMREQUEST ; 
 int /*<<< orphan*/  TRUE ; 
 char* aprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static CURLcode ftp_state_list(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct FTP *ftp = data->req.protop;

  /* If this output is to be machine-parsed, the NLST command might be better
     to use, since the LIST command output is not specified or standard in any
     way. It has turned out that the NLST list output is not the same on all
     servers either... */

  /*
     if FTPFILE_NOCWD was specified, we are currently in
     the user's home directory, so we should add the path
     as argument for the LIST / NLST / or custom command.
     Whether the server will support this, is uncertain.

     The other ftp_filemethods will CWD into dir/dir/ first and
     then just do LIST (in that case: nothing to do here)
  */
  char *cmd, *lstArg, *slashPos;
  const char *inpath = ftp->path;

  lstArg = NULL;
  if((data->set.ftp_filemethod == FTPFILE_NOCWD) &&
     inpath && inpath[0] && strchr(inpath, '/')) {
    size_t n = strlen(inpath);

    /* Check if path does not end with /, as then we cut off the file part */
    if(inpath[n - 1] != '/') {
      /* chop off the file part if format is dir/dir/file */
      slashPos = strrchr(inpath, '/');
      n = slashPos - inpath;
    }
    result = Curl_urldecode(data, inpath, n, &lstArg, NULL, TRUE);
    if(result)
      return result;
  }

  cmd = aprintf("%s%s%s",
                data->set.str[STRING_CUSTOMREQUEST]?
                data->set.str[STRING_CUSTOMREQUEST]:
                (data->set.ftp_list_only?"NLST":"LIST"),
                lstArg? " ": "",
                lstArg? lstArg: "");

  if(!cmd) {
    free(lstArg);
    return CURLE_OUT_OF_MEMORY;
  }

  result = Curl_pp_sendf(&conn->proto.ftpc.pp, "%s", cmd);

  free(lstArg);
  free(cmd);

  if(result)
    return result;

  state(conn, FTP_LIST);

  return result;
}