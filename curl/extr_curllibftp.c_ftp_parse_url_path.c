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
struct ftp_conn {int dirdepth; char** dirs; int diralloc; char* file; char const* prevpath; scalar_t__ prevmethod; void* cwddone; void* cwdfail; void* ctl_valid; } ;
struct TYPE_5__ {struct ftp_conn ftpc; } ;
struct connectdata {struct Curl_easy* data; TYPE_2__ proto; } ;
struct FTP {char* path; scalar_t__ transfer; } ;
struct TYPE_6__ {int ftp_filemethod; scalar_t__ upload; } ;
struct TYPE_4__ {struct FTP* protop; } ;
struct Curl_easy {TYPE_3__ set; TYPE_1__ req; } ;
typedef  int ssize_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_URL_MALFORMAT ; 
 scalar_t__ Curl_urldecode (struct Curl_easy*,char const*,size_t,char**,size_t*,void*) ; 
 void* FALSE ; 
#define  FTPFILE_MULTICWD 130 
#define  FTPFILE_NOCWD 129 
#define  FTPFILE_SINGLECWD 128 
 scalar_t__ FTPTRANSFER_BODY ; 
 void* TRUE ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freedirs (struct ftp_conn*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 char** realloc (char**,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* strdup (char*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,size_t) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static
CURLcode ftp_parse_url_path(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  /* the ftp struct is already inited in ftp_connect() */
  struct FTP *ftp = data->req.protop;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  const char *slash_pos;  /* position of the first '/' char in curpos */
  const char *path_to_use = ftp->path;
  const char *cur_pos;
  const char *filename = NULL;

  cur_pos = path_to_use; /* current position in path. point at the begin of
                            next path component */

  ftpc->ctl_valid = FALSE;
  ftpc->cwdfail = FALSE;

  switch(data->set.ftp_filemethod) {
  case FTPFILE_NOCWD:
    /* fastest, but less standard-compliant */

    /*
      The best time to check whether the path is a file or directory is right
      here. so:

      the first condition in the if() right here, is there just in case
      someone decides to set path to NULL one day
   */
    if(path_to_use[0] &&
       (path_to_use[strlen(path_to_use) - 1] != '/') )
      filename = path_to_use;  /* this is a full file path */
    /*
      else {
        ftpc->file is not used anywhere other than for operations on a file.
        In other words, never for directory operations.
        So we can safely leave filename as NULL here and use it as a
        argument in dir/file decisions.
      }
    */
    break;

  case FTPFILE_SINGLECWD:
    /* get the last slash */
    if(!path_to_use[0]) {
      /* no dir, no file */
      ftpc->dirdepth = 0;
      break;
    }
    slash_pos = strrchr(cur_pos, '/');
    if(slash_pos || !*cur_pos) {
      size_t dirlen = slash_pos-cur_pos;
      CURLcode result;

      ftpc->dirs = calloc(1, sizeof(ftpc->dirs[0]));
      if(!ftpc->dirs)
        return CURLE_OUT_OF_MEMORY;

      if(!dirlen)
        dirlen++;

      result = Curl_urldecode(conn->data, slash_pos ? cur_pos : "/",
                              slash_pos ? dirlen : 1,
                              &ftpc->dirs[0], NULL,
                              TRUE);
      if(result) {
        freedirs(ftpc);
        return result;
      }
      ftpc->dirdepth = 1; /* we consider it to be a single dir */
      filename = slash_pos ? slash_pos + 1 : cur_pos; /* rest is file name */
    }
    else
      filename = cur_pos;  /* this is a file name only */
    break;

  default: /* allow pretty much anything */
  case FTPFILE_MULTICWD:
    ftpc->dirdepth = 0;
    ftpc->diralloc = 5; /* default dir depth to allocate */
    ftpc->dirs = calloc(ftpc->diralloc, sizeof(ftpc->dirs[0]));
    if(!ftpc->dirs)
      return CURLE_OUT_OF_MEMORY;

    /* we have a special case for listing the root dir only */
    if(!strcmp(path_to_use, "/")) {
      cur_pos++; /* make it point to the zero byte */
      ftpc->dirs[0] = strdup("/");
      ftpc->dirdepth++;
    }
    else {
      /* parse the URL path into separate path components */
      while((slash_pos = strchr(cur_pos, '/')) != NULL) {
        /* 1 or 0 pointer offset to indicate absolute directory */
        ssize_t absolute_dir = ((cur_pos - ftp->path > 0) &&
                                (ftpc->dirdepth == 0))?1:0;

        /* seek out the next path component */
        if(slash_pos-cur_pos) {
          /* we skip empty path components, like "x//y" since the FTP command
             CWD requires a parameter and a non-existent parameter a) doesn't
             work on many servers and b) has no effect on the others. */
          size_t len = slash_pos - cur_pos + absolute_dir;
          CURLcode result =
            Curl_urldecode(conn->data, cur_pos - absolute_dir, len,
                           &ftpc->dirs[ftpc->dirdepth], NULL,
                           TRUE);
          if(result) {
            freedirs(ftpc);
            return result;
          }
        }
        else {
          cur_pos = slash_pos + 1; /* jump to the rest of the string */
          if(!ftpc->dirdepth) {
            /* path starts with a slash, add that as a directory */
            ftpc->dirs[ftpc->dirdepth] = strdup("/");
            if(!ftpc->dirs[ftpc->dirdepth++]) { /* run out of memory ... */
              failf(data, "no memory");
              freedirs(ftpc);
              return CURLE_OUT_OF_MEMORY;
            }
          }
          continue;
        }

        cur_pos = slash_pos + 1; /* jump to the rest of the string */
        if(++ftpc->dirdepth >= ftpc->diralloc) {
          /* enlarge array */
          char **bigger;
          ftpc->diralloc *= 2; /* double the size each time */
          bigger = realloc(ftpc->dirs, ftpc->diralloc * sizeof(ftpc->dirs[0]));
          if(!bigger) {
            freedirs(ftpc);
            return CURLE_OUT_OF_MEMORY;
          }
          ftpc->dirs = bigger;
        }
      }
    }
    filename = cur_pos;  /* the rest is the file name */
    break;
  } /* switch */

  if(filename && *filename) {
    CURLcode result =
      Curl_urldecode(conn->data, filename, 0,  &ftpc->file, NULL, TRUE);

    if(result) {
      freedirs(ftpc);
      return result;
    }
  }
  else
    ftpc->file = NULL; /* instead of point to a zero byte, we make it a NULL
                          pointer */

  if(data->set.upload && !ftpc->file && (ftp->transfer == FTPTRANSFER_BODY)) {
    /* We need a file name when uploading. Return error! */
    failf(data, "Uploading to a URL without a file name!");
    return CURLE_URL_MALFORMAT;
  }

  ftpc->cwddone = FALSE; /* default to not done */

  if(ftpc->prevpath) {
    /* prevpath is "raw" so we convert the input path before we compare the
       strings */
    size_t dlen;
    char *path;
    CURLcode result =
      Curl_urldecode(conn->data, ftp->path, 0, &path, &dlen, TRUE);
    if(result) {
      freedirs(ftpc);
      return result;
    }

    dlen -= ftpc->file?strlen(ftpc->file):0;
    if((dlen == strlen(ftpc->prevpath)) &&
       !strncmp(path, ftpc->prevpath, dlen) &&
       (ftpc->prevmethod == data->set.ftp_filemethod)) {
      infof(data, "Request has same path as previous transfer\n");
      ftpc->cwddone = TRUE;
    }
    free(path);
  }

  return CURLE_OK;
}