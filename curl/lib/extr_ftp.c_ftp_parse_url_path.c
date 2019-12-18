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
struct ftp_conn {char** dirs; int dirdepth; char const* file; char* prevpath; void* cwddone; void* cwdfail; void* ctl_valid; } ;
struct TYPE_7__ {scalar_t__ reuse; } ;
struct TYPE_6__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_3__ bits; TYPE_2__ proto; struct Curl_easy* data; } ;
struct FTP {scalar_t__ transfer; int /*<<< orphan*/  path; } ;
struct TYPE_8__ {int ftp_filemethod; scalar_t__ upload; } ;
struct TYPE_5__ {struct FTP* protop; } ;
struct Curl_easy {TYPE_4__ set; TYPE_1__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_URL_MALFORMAT ; 
 scalar_t__ Curl_urldecode (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,size_t*,void*) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 void* FALSE ; 
#define  FTPFILE_MULTICWD 130 
#define  FTPFILE_NOCWD 129 
#define  FTPFILE_SINGLECWD 128 
 scalar_t__ FTPTRANSFER_BODY ; 
 void* TRUE ; 
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 char* strchr (char const*,char) ; 
 char const* strdup (char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static
CURLcode ftp_parse_url_path(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  /* the ftp struct is already inited in ftp_connect() */
  struct FTP *ftp = data->req.protop;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  const char *slashPos = NULL;
  const char *fileName = NULL;
  CURLcode result = CURLE_OK;
  char *rawPath = NULL; /* url-decoded "raw" path */
  size_t pathLen = 0;

  ftpc->ctl_valid = FALSE;
  ftpc->cwdfail = FALSE;

  /* url-decode ftp path before further evaluation */
  result = Curl_urldecode(data, ftp->path, 0, &rawPath, &pathLen, TRUE);
  if(result)
    return result;

  switch(data->set.ftp_filemethod) {
    case FTPFILE_NOCWD: /* fastest, but less standard-compliant */

      if((pathLen > 0) && (rawPath[pathLen - 1] != '/'))
          fileName = rawPath;  /* this is a full file path */
      /*
        else: ftpc->file is not used anywhere other than for operations on
              a file. In other words, never for directory operations.
              So we can safely leave filename as NULL here and use it as a
              argument in dir/file decisions.
      */
      break;

    case FTPFILE_SINGLECWD:
      slashPos = strrchr(rawPath, '/');
      if(slashPos) {
        /* get path before last slash, except for / */
        size_t dirlen = slashPos - rawPath;
        if(dirlen == 0)
            dirlen++;

        ftpc->dirs = calloc(1, sizeof(ftpc->dirs[0]));
        if(!ftpc->dirs) {
          free(rawPath);
          return CURLE_OUT_OF_MEMORY;
        }

        ftpc->dirs[0] = calloc(1, dirlen + 1);
        if(!ftpc->dirs[0]) {
          free(rawPath);
          return CURLE_OUT_OF_MEMORY;
        }

        strncpy(ftpc->dirs[0], rawPath, dirlen);
        ftpc->dirdepth = 1; /* we consider it to be a single dir */
        fileName = slashPos + 1; /* rest is file name */
      }
      else
        fileName = rawPath; /* file name only (or empty) */
      break;

    default: /* allow pretty much anything */
    case FTPFILE_MULTICWD: {
      /* current position: begin of next path component */
      const char *curPos = rawPath;

      int dirAlloc = 0; /* number of entries allocated for the 'dirs' array */
      const char *str = rawPath;
      for(; *str != 0; ++str)
        if (*str == '/')
          ++dirAlloc;

      if(dirAlloc > 0) {
        ftpc->dirs = calloc(dirAlloc, sizeof(ftpc->dirs[0]));
        if(!ftpc->dirs) {
          free(rawPath);
          return CURLE_OUT_OF_MEMORY;
        }

        /* parse the URL path into separate path components */
        while((slashPos = strchr(curPos, '/')) != NULL) {
          size_t compLen = slashPos - curPos;

          /* path starts with a slash: add that as a directory */
          if((compLen == 0) && (ftpc->dirdepth == 0))
            ++compLen;

          /* we skip empty path components, like "x//y" since the FTP command
             CWD requires a parameter and a non-existent parameter a) doesn't
             work on many servers and b) has no effect on the others. */
          if(compLen > 0) {
            char *comp = calloc(1, compLen + 1);
            if(!comp) {
              free(rawPath);
              return CURLE_OUT_OF_MEMORY;
            }
            strncpy(comp, curPos, compLen);
            ftpc->dirs[ftpc->dirdepth++] = comp;
          }
          curPos = slashPos + 1;
        }
      }
      DEBUGASSERT(ftpc->dirdepth <= dirAlloc);
      fileName = curPos; /* the rest is the file name (or empty) */
    }
    break;
  } /* switch */

  if(fileName && *fileName)
    ftpc->file = strdup(fileName);
  else
    ftpc->file = NULL; /* instead of point to a zero byte,
                            we make it a NULL pointer */

  if(data->set.upload && !ftpc->file && (ftp->transfer == FTPTRANSFER_BODY)) {
    /* We need a file name when uploading. Return error! */
    failf(data, "Uploading to a URL without a file name!");
    free(rawPath);
    return CURLE_URL_MALFORMAT;
  }

  ftpc->cwddone = FALSE; /* default to not done */

  if((data->set.ftp_filemethod == FTPFILE_NOCWD) && (rawPath[0] == '/'))
    ftpc->cwddone = TRUE; /* skip CWD for absolute paths */
  else { /* newly created FTP connections are already in entry path */
    const char *oldPath = conn->bits.reuse ? ftpc->prevpath : "";
    if(oldPath) {
      size_t n = pathLen;
      if(data->set.ftp_filemethod == FTPFILE_NOCWD)
        n = 0; /* CWD to entry for relative paths */
      else
        n -= ftpc->file?strlen(ftpc->file):0;

      if((strlen(oldPath) == n) && !strncmp(rawPath, oldPath, n)) {
        infof(data, "Request has same path as previous transfer\n");
        ftpc->cwddone = TRUE;
      }
    }
  }

  free(rawPath);
  return CURLE_OK;
}