#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ st_size; } ;
typedef  TYPE_4__ struct_stat ;
struct connectdata {struct Curl_easy* data; } ;
struct FILEPROTO {int /*<<< orphan*/  path; } ;
struct TYPE_8__ {char* buffer; scalar_t__ resume_from; int infilesize; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  new_file_perms; } ;
struct TYPE_6__ {char* upload_fromhere; struct FILEPROTO* protop; } ;
struct Curl_easy {TYPE_3__ state; TYPE_2__ set; TYPE_1__ req; } ;
typedef  scalar_t__ curl_off_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_ABORTED_BY_CALLBACK ; 
 scalar_t__ CURLE_FILE_COULDNT_READ_FILE ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_SEND_ERROR ; 
 scalar_t__ CURLE_WRITE_ERROR ; 
 scalar_t__ Curl_fillreadbuffer (struct connectdata*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  Curl_now () ; 
 int /*<<< orphan*/  Curl_pgrsSetUploadCounter (struct Curl_easy*,scalar_t__) ; 
 int /*<<< orphan*/  Curl_pgrsSetUploadSize (struct Curl_easy*,int) ; 
 scalar_t__ Curl_pgrsUpdate (struct connectdata*) ; 
 scalar_t__ Curl_speedcheck (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIRSEP ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,TYPE_4__*) ; 
 int open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t write (int,char const*,size_t) ; 

__attribute__((used)) static CURLcode file_upload(struct connectdata *conn)
{
  struct FILEPROTO *file = conn->data->req.protop;
  const char *dir = strchr(file->path, DIRSEP);
  int fd;
  int mode;
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  char *buf = data->state.buffer;
  curl_off_t bytecount = 0;
  struct_stat file_stat;
  const char *buf2;

  /*
   * Since FILE: doesn't do the full init, we need to provide some extra
   * assignments here.
   */
  conn->data->req.upload_fromhere = buf;

  if(!dir)
    return CURLE_FILE_COULDNT_READ_FILE; /* fix: better error code */

  if(!dir[1])
    return CURLE_FILE_COULDNT_READ_FILE; /* fix: better error code */

#ifdef O_BINARY
#define MODE_DEFAULT O_WRONLY|O_CREAT|O_BINARY
#else
#define MODE_DEFAULT O_WRONLY|O_CREAT
#endif

  if(data->state.resume_from)
    mode = MODE_DEFAULT|O_APPEND;
  else
    mode = MODE_DEFAULT|O_TRUNC;

  fd = open(file->path, mode, conn->data->set.new_file_perms);
  if(fd < 0) {
    failf(data, "Can't open %s for writing", file->path);
    return CURLE_WRITE_ERROR;
  }

  if(-1 != data->state.infilesize)
    /* known size of data to "upload" */
    Curl_pgrsSetUploadSize(data, data->state.infilesize);

  /* treat the negative resume offset value as the case of "-" */
  if(data->state.resume_from < 0) {
    if(fstat(fd, &file_stat)) {
      close(fd);
      failf(data, "Can't get the size of %s", file->path);
      return CURLE_WRITE_ERROR;
    }
    data->state.resume_from = (curl_off_t)file_stat.st_size;
  }

  while(!result) {
    size_t nread;
    size_t nwrite;
    size_t readcount;
    result = Curl_fillreadbuffer(conn, data->set.buffer_size, &readcount);
    if(result)
      break;

    if(!readcount)
      break;

    nread = readcount;

    /*skip bytes before resume point*/
    if(data->state.resume_from) {
      if((curl_off_t)nread <= data->state.resume_from) {
        data->state.resume_from -= nread;
        nread = 0;
        buf2 = buf;
      }
      else {
        buf2 = buf + data->state.resume_from;
        nread -= (size_t)data->state.resume_from;
        data->state.resume_from = 0;
      }
    }
    else
      buf2 = buf;

    /* write the data to the target */
    nwrite = write(fd, buf2, nread);
    if(nwrite != nread) {
      result = CURLE_SEND_ERROR;
      break;
    }

    bytecount += nread;

    Curl_pgrsSetUploadCounter(data, bytecount);

    if(Curl_pgrsUpdate(conn))
      result = CURLE_ABORTED_BY_CALLBACK;
    else
      result = Curl_speedcheck(data, Curl_now());
  }
  if(!result && Curl_pgrsUpdate(conn))
    result = CURLE_ABORTED_BY_CALLBACK;

  close(fd);

  return result;
}