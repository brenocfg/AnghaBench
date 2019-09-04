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
struct ftp_wc {struct ftp_parselist_data* parser; } ;
struct TYPE_14__ {int time; int dirorsize; int filename; } ;
struct TYPE_15__ {int main; TYPE_6__ sub; } ;
struct TYPE_11__ {int total_dirsize; int hlinks; int user; int group; int size; int time; int symlink; int filename; } ;
struct TYPE_12__ {int main; TYPE_3__ sub; } ;
struct TYPE_16__ {TYPE_7__ NT; TYPE_4__ UNIX; } ;
struct TYPE_13__ {int perm; int user; int group; int time; int filename; int symlink_target; } ;
struct ftp_parselist_data {int os_type; int item_offset; size_t item_length; struct fileinfo* file_data; void* error; TYPE_8__ state; TYPE_5__ offsets; } ;
struct curl_fileinfo {char* b_data; int b_size; int b_used; unsigned int perm; long hardlinks; int /*<<< orphan*/  flags; void* filetype; int /*<<< orphan*/  size; } ;
struct fileinfo {struct curl_fileinfo info; } ;
struct connectdata {TYPE_2__* data; } ;
typedef  int /*<<< orphan*/  curl_off_t ;
struct TYPE_9__ {struct ftp_wc* protdata; } ;
struct TYPE_10__ {TYPE_1__ wildcard; } ;
typedef  void* CURLcode ;

/* Variables and functions */
 void* CURLE_FTP_BAD_FILE_LIST ; 
 void* CURLE_OUT_OF_MEMORY ; 
 void* CURLFILETYPE_DEVICE_BLOCK ; 
 void* CURLFILETYPE_DEVICE_CHAR ; 
 void* CURLFILETYPE_DIRECTORY ; 
 void* CURLFILETYPE_DOOR ; 
 void* CURLFILETYPE_FILE ; 
 void* CURLFILETYPE_NAMEDPIPE ; 
 void* CURLFILETYPE_SOCKET ; 
 void* CURLFILETYPE_SYMLINK ; 
 int /*<<< orphan*/  CURLFINFOFLAG_KNOWN_HLINKCOUNT ; 
 int /*<<< orphan*/  CURLFINFOFLAG_KNOWN_PERM ; 
 int /*<<< orphan*/  CURLFINFOFLAG_KNOWN_SIZE ; 
 int /*<<< orphan*/  CURL_OFF_T_MAX ; 
 int /*<<< orphan*/  CURL_OFF_T_MIN ; 
 struct fileinfo* Curl_fileinfo_alloc () ; 
 int /*<<< orphan*/  Curl_fileinfo_cleanup (struct fileinfo*) ; 
 int FTP_BUFFER_ALLOCSIZE ; 
 unsigned int FTP_LP_MALFORMATED_PERM ; 
 int /*<<< orphan*/  ISALNUM (char) ; 
 int /*<<< orphan*/  ISDIGIT (char) ; 
 int /*<<< orphan*/  ISSPACE (char) ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
#define  OS_TYPE_UNIX 177 
 int OS_TYPE_UNKNOWN ; 
#define  OS_TYPE_WIN_NT 176 
#define  PL_UNIX_FILENAME 175 
#define  PL_UNIX_FILENAME_NAME 174 
#define  PL_UNIX_FILENAME_PRESPACE 173 
#define  PL_UNIX_FILENAME_WINDOWSEOL 172 
#define  PL_UNIX_FILETYPE 171 
#define  PL_UNIX_GROUP 170 
#define  PL_UNIX_GROUP_NAME 169 
#define  PL_UNIX_GROUP_PRESPACE 168 
#define  PL_UNIX_HLINKS 167 
#define  PL_UNIX_HLINKS_NUMBER 166 
#define  PL_UNIX_HLINKS_PRESPACE 165 
#define  PL_UNIX_PERMISSION 164 
#define  PL_UNIX_SIZE 163 
#define  PL_UNIX_SIZE_NUMBER 162 
#define  PL_UNIX_SIZE_PRESPACE 161 
#define  PL_UNIX_SYMLINK 160 
#define  PL_UNIX_SYMLINK_NAME 159 
#define  PL_UNIX_SYMLINK_PRESPACE 158 
#define  PL_UNIX_SYMLINK_PRETARGET1 157 
#define  PL_UNIX_SYMLINK_PRETARGET2 156 
#define  PL_UNIX_SYMLINK_PRETARGET3 155 
#define  PL_UNIX_SYMLINK_PRETARGET4 154 
#define  PL_UNIX_SYMLINK_TARGET 153 
#define  PL_UNIX_SYMLINK_WINDOWSEOL 152 
#define  PL_UNIX_TIME 151 
#define  PL_UNIX_TIME_PART1 150 
#define  PL_UNIX_TIME_PART2 149 
#define  PL_UNIX_TIME_PART3 148 
#define  PL_UNIX_TIME_PREPART1 147 
#define  PL_UNIX_TIME_PREPART2 146 
#define  PL_UNIX_TIME_PREPART3 145 
#define  PL_UNIX_TOTALSIZE 144 
#define  PL_UNIX_TOTALSIZE_INIT 143 
#define  PL_UNIX_TOTALSIZE_READING 142 
#define  PL_UNIX_USER 141 
#define  PL_UNIX_USER_PARSING 140 
#define  PL_UNIX_USER_PRESPACE 139 
#define  PL_WINNT_DATE 138 
#define  PL_WINNT_DIRORSIZE 137 
#define  PL_WINNT_DIRORSIZE_CONTENT 136 
#define  PL_WINNT_DIRORSIZE_PRESPACE 135 
#define  PL_WINNT_FILENAME 134 
#define  PL_WINNT_FILENAME_CONTENT 133 
#define  PL_WINNT_FILENAME_PRESPACE 132 
#define  PL_WINNT_FILENAME_WINEOL 131 
#define  PL_WINNT_TIME 130 
#define  PL_WINNT_TIME_PRESPACE 129 
#define  PL_WINNT_TIME_TIME 128 
 int /*<<< orphan*/  curlx_strtoofft (char*,char**,int,int /*<<< orphan*/ *) ; 
 unsigned int ftp_pl_get_permission (char*) ; 
 void* ftp_pl_insert_finfo (struct connectdata*,struct fileinfo*) ; 
 char* malloc (int) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 long strtol (char*,char**,int) ; 

size_t Curl_ftp_parselist(char *buffer, size_t size, size_t nmemb,
                          void *connptr)
{
  size_t bufflen = size*nmemb;
  struct connectdata *conn = (struct connectdata *)connptr;
  struct ftp_wc *ftpwc = conn->data->wildcard.protdata;
  struct ftp_parselist_data *parser = ftpwc->parser;
  struct fileinfo *infop;
  struct curl_fileinfo *finfo;
  unsigned long i = 0;
  CURLcode result;
  size_t retsize = bufflen;

  if(parser->error) { /* error in previous call */
    /* scenario:
     * 1. call => OK..
     * 2. call => OUT_OF_MEMORY (or other error)
     * 3. (last) call => is skipped RIGHT HERE and the error is hadled later
     *    in wc_statemach()
     */
    goto fail;
  }

  if(parser->os_type == OS_TYPE_UNKNOWN && bufflen > 0) {
    /* considering info about FILE response format */
    parser->os_type = (buffer[0] >= '0' && buffer[0] <= '9') ?
                       OS_TYPE_WIN_NT : OS_TYPE_UNIX;
  }

  while(i < bufflen) { /* FSM */

    char c = buffer[i];
    if(!parser->file_data) { /* tmp file data is not allocated yet */
      parser->file_data = Curl_fileinfo_alloc();
      if(!parser->file_data) {
        parser->error = CURLE_OUT_OF_MEMORY;
        goto fail;
      }
      parser->file_data->info.b_data = malloc(FTP_BUFFER_ALLOCSIZE);
      if(!parser->file_data->info.b_data) {
        parser->error = CURLE_OUT_OF_MEMORY;
        goto fail;
      }
      parser->file_data->info.b_size = FTP_BUFFER_ALLOCSIZE;
      parser->item_offset = 0;
      parser->item_length = 0;
    }

    infop = parser->file_data;
    finfo = &infop->info;
    finfo->b_data[finfo->b_used++] = c;

    if(finfo->b_used >= finfo->b_size - 1) {
      /* if it is important, extend buffer space for file data */
      char *tmp = realloc(finfo->b_data,
                          finfo->b_size + FTP_BUFFER_ALLOCSIZE);
      if(tmp) {
        finfo->b_size += FTP_BUFFER_ALLOCSIZE;
        finfo->b_data = tmp;
      }
      else {
        Curl_fileinfo_cleanup(parser->file_data);
        parser->file_data = NULL;
        parser->error = CURLE_OUT_OF_MEMORY;
        goto fail;
      }
    }

    switch(parser->os_type) {
    case OS_TYPE_UNIX:
      switch(parser->state.UNIX.main) {
      case PL_UNIX_TOTALSIZE:
        switch(parser->state.UNIX.sub.total_dirsize) {
        case PL_UNIX_TOTALSIZE_INIT:
          if(c == 't') {
            parser->state.UNIX.sub.total_dirsize = PL_UNIX_TOTALSIZE_READING;
            parser->item_length++;
          }
          else {
            parser->state.UNIX.main = PL_UNIX_FILETYPE;
            /* start FSM again not considering size of directory */
            finfo->b_used = 0;
            continue;
          }
          break;
        case PL_UNIX_TOTALSIZE_READING:
          parser->item_length++;
          if(c == '\r') {
            parser->item_length--;
            finfo->b_used--;
          }
          else if(c == '\n') {
            finfo->b_data[parser->item_length - 1] = 0;
            if(strncmp("total ", finfo->b_data, 6) == 0) {
              char *endptr = finfo->b_data + 6;
              /* here we can deal with directory size, pass the leading white
                 spaces and then the digits */
              while(ISSPACE(*endptr))
                endptr++;
              while(ISDIGIT(*endptr))
                endptr++;
              if(*endptr != 0) {
                parser->error = CURLE_FTP_BAD_FILE_LIST;
                goto fail;
              }
              parser->state.UNIX.main = PL_UNIX_FILETYPE;
              finfo->b_used = 0;
            }
            else {
              parser->error = CURLE_FTP_BAD_FILE_LIST;
              goto fail;
            }
          }
          break;
        }
        break;
      case PL_UNIX_FILETYPE:
        switch(c) {
        case '-':
          finfo->filetype = CURLFILETYPE_FILE;
          break;
        case 'd':
          finfo->filetype = CURLFILETYPE_DIRECTORY;
          break;
        case 'l':
          finfo->filetype = CURLFILETYPE_SYMLINK;
          break;
        case 'p':
          finfo->filetype = CURLFILETYPE_NAMEDPIPE;
          break;
        case 's':
          finfo->filetype = CURLFILETYPE_SOCKET;
          break;
        case 'c':
          finfo->filetype = CURLFILETYPE_DEVICE_CHAR;
          break;
        case 'b':
          finfo->filetype = CURLFILETYPE_DEVICE_BLOCK;
          break;
        case 'D':
          finfo->filetype = CURLFILETYPE_DOOR;
          break;
        default:
          parser->error = CURLE_FTP_BAD_FILE_LIST;
          goto fail;
        }
        parser->state.UNIX.main = PL_UNIX_PERMISSION;
        parser->item_length = 0;
        parser->item_offset = 1;
        break;
      case PL_UNIX_PERMISSION:
        parser->item_length++;
        if(parser->item_length <= 9) {
          if(!strchr("rwx-tTsS", c)) {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
        }
        else if(parser->item_length == 10) {
          unsigned int perm;
          if(c != ' ') {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          finfo->b_data[10] = 0; /* terminate permissions */
          perm = ftp_pl_get_permission(finfo->b_data + parser->item_offset);
          if(perm & FTP_LP_MALFORMATED_PERM) {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          parser->file_data->info.flags |= CURLFINFOFLAG_KNOWN_PERM;
          parser->file_data->info.perm = perm;
          parser->offsets.perm = parser->item_offset;

          parser->item_length = 0;
          parser->state.UNIX.main = PL_UNIX_HLINKS;
          parser->state.UNIX.sub.hlinks = PL_UNIX_HLINKS_PRESPACE;
        }
        break;
      case PL_UNIX_HLINKS:
        switch(parser->state.UNIX.sub.hlinks) {
        case PL_UNIX_HLINKS_PRESPACE:
          if(c != ' ') {
            if(c >= '0' && c <= '9') {
              parser->item_offset = finfo->b_used - 1;
              parser->item_length = 1;
              parser->state.UNIX.sub.hlinks = PL_UNIX_HLINKS_NUMBER;
            }
            else {
              parser->error = CURLE_FTP_BAD_FILE_LIST;
              goto fail;
            }
          }
          break;
        case PL_UNIX_HLINKS_NUMBER:
          parser->item_length ++;
          if(c == ' ') {
            char *p;
            long int hlinks;
            finfo->b_data[parser->item_offset + parser->item_length - 1] = 0;
            hlinks = strtol(finfo->b_data + parser->item_offset, &p, 10);
            if(p[0] == '\0' && hlinks != LONG_MAX && hlinks != LONG_MIN) {
              parser->file_data->info.flags |= CURLFINFOFLAG_KNOWN_HLINKCOUNT;
              parser->file_data->info.hardlinks = hlinks;
            }
            parser->item_length = 0;
            parser->item_offset = 0;
            parser->state.UNIX.main = PL_UNIX_USER;
            parser->state.UNIX.sub.user = PL_UNIX_USER_PRESPACE;
          }
          else if(c < '0' || c > '9') {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        }
        break;
      case PL_UNIX_USER:
        switch(parser->state.UNIX.sub.user) {
        case PL_UNIX_USER_PRESPACE:
          if(c != ' ') {
            parser->item_offset = finfo->b_used - 1;
            parser->item_length = 1;
            parser->state.UNIX.sub.user = PL_UNIX_USER_PARSING;
          }
          break;
        case PL_UNIX_USER_PARSING:
          parser->item_length++;
          if(c == ' ') {
            finfo->b_data[parser->item_offset + parser->item_length - 1] = 0;
            parser->offsets.user = parser->item_offset;
            parser->state.UNIX.main = PL_UNIX_GROUP;
            parser->state.UNIX.sub.group = PL_UNIX_GROUP_PRESPACE;
            parser->item_offset = 0;
            parser->item_length = 0;
          }
          break;
        }
        break;
      case PL_UNIX_GROUP:
        switch(parser->state.UNIX.sub.group) {
        case PL_UNIX_GROUP_PRESPACE:
          if(c != ' ') {
            parser->item_offset = finfo->b_used - 1;
            parser->item_length = 1;
            parser->state.UNIX.sub.group = PL_UNIX_GROUP_NAME;
          }
          break;
        case PL_UNIX_GROUP_NAME:
          parser->item_length++;
          if(c == ' ') {
            finfo->b_data[parser->item_offset + parser->item_length - 1] = 0;
            parser->offsets.group = parser->item_offset;
            parser->state.UNIX.main = PL_UNIX_SIZE;
            parser->state.UNIX.sub.size = PL_UNIX_SIZE_PRESPACE;
            parser->item_offset = 0;
            parser->item_length = 0;
          }
          break;
        }
        break;
      case PL_UNIX_SIZE:
        switch(parser->state.UNIX.sub.size) {
        case PL_UNIX_SIZE_PRESPACE:
          if(c != ' ') {
            if(c >= '0' && c <= '9') {
              parser->item_offset = finfo->b_used - 1;
              parser->item_length = 1;
              parser->state.UNIX.sub.size = PL_UNIX_SIZE_NUMBER;
            }
            else {
              parser->error = CURLE_FTP_BAD_FILE_LIST;
              goto fail;
            }
          }
          break;
        case PL_UNIX_SIZE_NUMBER:
          parser->item_length++;
          if(c == ' ') {
            char *p;
            curl_off_t fsize;
            finfo->b_data[parser->item_offset + parser->item_length - 1] = 0;
            if(!curlx_strtoofft(finfo->b_data + parser->item_offset,
                                &p, 10, &fsize)) {
              if(p[0] == '\0' && fsize != CURL_OFF_T_MAX &&
                 fsize != CURL_OFF_T_MIN) {
                parser->file_data->info.flags |= CURLFINFOFLAG_KNOWN_SIZE;
                parser->file_data->info.size = fsize;
              }
              parser->item_length = 0;
              parser->item_offset = 0;
              parser->state.UNIX.main = PL_UNIX_TIME;
              parser->state.UNIX.sub.time = PL_UNIX_TIME_PREPART1;
            }
          }
          else if(!ISDIGIT(c)) {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        }
        break;
      case PL_UNIX_TIME:
        switch(parser->state.UNIX.sub.time) {
        case PL_UNIX_TIME_PREPART1:
          if(c != ' ') {
            if(ISALNUM(c)) {
              parser->item_offset = finfo->b_used -1;
              parser->item_length = 1;
              parser->state.UNIX.sub.time = PL_UNIX_TIME_PART1;
            }
            else {
              parser->error = CURLE_FTP_BAD_FILE_LIST;
              goto fail;
            }
          }
          break;
        case PL_UNIX_TIME_PART1:
          parser->item_length++;
          if(c == ' ') {
            parser->state.UNIX.sub.time = PL_UNIX_TIME_PREPART2;
          }
          else if(!ISALNUM(c) && c != '.') {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        case PL_UNIX_TIME_PREPART2:
          parser->item_length++;
          if(c != ' ') {
            if(ISALNUM(c)) {
              parser->state.UNIX.sub.time = PL_UNIX_TIME_PART2;
            }
            else {
              parser->error = CURLE_FTP_BAD_FILE_LIST;
              goto fail;
            }
          }
          break;
        case PL_UNIX_TIME_PART2:
          parser->item_length++;
          if(c == ' ') {
            parser->state.UNIX.sub.time = PL_UNIX_TIME_PREPART3;
          }
          else if(!ISALNUM(c) && c != '.') {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        case PL_UNIX_TIME_PREPART3:
          parser->item_length++;
          if(c != ' ') {
            if(ISALNUM(c)) {
              parser->state.UNIX.sub.time = PL_UNIX_TIME_PART3;
            }
            else {
              parser->error = CURLE_FTP_BAD_FILE_LIST;
              goto fail;
            }
          }
          break;
        case PL_UNIX_TIME_PART3:
          parser->item_length++;
          if(c == ' ') {
            finfo->b_data[parser->item_offset + parser->item_length -1] = 0;
            parser->offsets.time = parser->item_offset;
            /*
              if(ftp_pl_gettime(parser, finfo->b_data + parser->item_offset)) {
                parser->file_data->flags |= CURLFINFOFLAG_KNOWN_TIME;
              }
            */
            if(finfo->filetype == CURLFILETYPE_SYMLINK) {
              parser->state.UNIX.main = PL_UNIX_SYMLINK;
              parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_PRESPACE;
            }
            else {
              parser->state.UNIX.main = PL_UNIX_FILENAME;
              parser->state.UNIX.sub.filename = PL_UNIX_FILENAME_PRESPACE;
            }
          }
          else if(!ISALNUM(c) && c != '.' && c != ':') {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        }
        break;
      case PL_UNIX_FILENAME:
        switch(parser->state.UNIX.sub.filename) {
        case PL_UNIX_FILENAME_PRESPACE:
          if(c != ' ') {
            parser->item_offset = finfo->b_used - 1;
            parser->item_length = 1;
            parser->state.UNIX.sub.filename = PL_UNIX_FILENAME_NAME;
          }
          break;
        case PL_UNIX_FILENAME_NAME:
          parser->item_length++;
          if(c == '\r') {
            parser->state.UNIX.sub.filename = PL_UNIX_FILENAME_WINDOWSEOL;
          }
          else if(c == '\n') {
            finfo->b_data[parser->item_offset + parser->item_length - 1] = 0;
            parser->offsets.filename = parser->item_offset;
            parser->state.UNIX.main = PL_UNIX_FILETYPE;
            result = ftp_pl_insert_finfo(conn, infop);
            if(result) {
              parser->error = result;
              goto fail;
            }
          }
          break;
        case PL_UNIX_FILENAME_WINDOWSEOL:
          if(c == '\n') {
            finfo->b_data[parser->item_offset + parser->item_length - 1] = 0;
            parser->offsets.filename = parser->item_offset;
            parser->state.UNIX.main = PL_UNIX_FILETYPE;
            result = ftp_pl_insert_finfo(conn, infop);
            if(result) {
              parser->error = result;
              goto fail;
            }
          }
          else {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        }
        break;
      case PL_UNIX_SYMLINK:
        switch(parser->state.UNIX.sub.symlink) {
        case PL_UNIX_SYMLINK_PRESPACE:
          if(c != ' ') {
            parser->item_offset = finfo->b_used - 1;
            parser->item_length = 1;
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_NAME;
          }
          break;
        case PL_UNIX_SYMLINK_NAME:
          parser->item_length++;
          if(c == ' ') {
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_PRETARGET1;
          }
          else if(c == '\r' || c == '\n') {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        case PL_UNIX_SYMLINK_PRETARGET1:
          parser->item_length++;
          if(c == '-') {
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_PRETARGET2;
          }
          else if(c == '\r' || c == '\n') {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          else {
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_NAME;
          }
          break;
        case PL_UNIX_SYMLINK_PRETARGET2:
          parser->item_length++;
          if(c == '>') {
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_PRETARGET3;
          }
          else if(c == '\r' || c == '\n') {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          else {
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_NAME;
          }
          break;
        case PL_UNIX_SYMLINK_PRETARGET3:
          parser->item_length++;
          if(c == ' ') {
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_PRETARGET4;
            /* now place where is symlink following */
            finfo->b_data[parser->item_offset + parser->item_length - 4] = 0;
            parser->offsets.filename = parser->item_offset;
            parser->item_length = 0;
            parser->item_offset = 0;
          }
          else if(c == '\r' || c == '\n') {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          else {
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_NAME;
          }
          break;
        case PL_UNIX_SYMLINK_PRETARGET4:
          if(c != '\r' && c != '\n') {
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_TARGET;
            parser->item_offset = finfo->b_used - 1;
            parser->item_length = 1;
          }
          else {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        case PL_UNIX_SYMLINK_TARGET:
          parser->item_length++;
          if(c == '\r') {
            parser->state.UNIX.sub.symlink = PL_UNIX_SYMLINK_WINDOWSEOL;
          }
          else if(c == '\n') {
            finfo->b_data[parser->item_offset + parser->item_length - 1] = 0;
            parser->offsets.symlink_target = parser->item_offset;
            result = ftp_pl_insert_finfo(conn, infop);
            if(result) {
              parser->error = result;
              goto fail;
            }
            parser->state.UNIX.main = PL_UNIX_FILETYPE;
          }
          break;
        case PL_UNIX_SYMLINK_WINDOWSEOL:
          if(c == '\n') {
            finfo->b_data[parser->item_offset + parser->item_length - 1] = 0;
            parser->offsets.symlink_target = parser->item_offset;
            result = ftp_pl_insert_finfo(conn, infop);
            if(result) {
              parser->error = result;
              goto fail;
            }
            parser->state.UNIX.main = PL_UNIX_FILETYPE;
          }
          else {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        }
        break;
      }
      break;
    case OS_TYPE_WIN_NT:
      switch(parser->state.NT.main) {
      case PL_WINNT_DATE:
        parser->item_length++;
        if(parser->item_length < 9) {
          if(!strchr("0123456789-", c)) { /* only simple control */
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
        }
        else if(parser->item_length == 9) {
          if(c == ' ') {
            parser->state.NT.main = PL_WINNT_TIME;
            parser->state.NT.sub.time = PL_WINNT_TIME_PRESPACE;
          }
          else {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
        }
        else {
          parser->error = CURLE_FTP_BAD_FILE_LIST;
          goto fail;
        }
        break;
      case PL_WINNT_TIME:
        parser->item_length++;
        switch(parser->state.NT.sub.time) {
        case PL_WINNT_TIME_PRESPACE:
          if(!ISSPACE(c)) {
            parser->state.NT.sub.time = PL_WINNT_TIME_TIME;
          }
          break;
        case PL_WINNT_TIME_TIME:
          if(c == ' ') {
            parser->offsets.time = parser->item_offset;
            finfo->b_data[parser->item_offset + parser->item_length -1] = 0;
            parser->state.NT.main = PL_WINNT_DIRORSIZE;
            parser->state.NT.sub.dirorsize = PL_WINNT_DIRORSIZE_PRESPACE;
            parser->item_length = 0;
          }
          else if(!strchr("APM0123456789:", c)) {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        }
        break;
      case PL_WINNT_DIRORSIZE:
        switch(parser->state.NT.sub.dirorsize) {
        case PL_WINNT_DIRORSIZE_PRESPACE:
          if(c != ' ') {
            parser->item_offset = finfo->b_used - 1;
            parser->item_length = 1;
            parser->state.NT.sub.dirorsize = PL_WINNT_DIRORSIZE_CONTENT;
          }
          break;
        case PL_WINNT_DIRORSIZE_CONTENT:
          parser->item_length ++;
          if(c == ' ') {
            finfo->b_data[parser->item_offset + parser->item_length - 1] = 0;
            if(strcmp("<DIR>", finfo->b_data + parser->item_offset) == 0) {
              finfo->filetype = CURLFILETYPE_DIRECTORY;
              finfo->size = 0;
            }
            else {
              char *endptr;
              if(curlx_strtoofft(finfo->b_data +
                                 parser->item_offset,
                                 &endptr, 10, &finfo->size)) {
                parser->error = CURLE_FTP_BAD_FILE_LIST;
                goto fail;
              }
              /* correct file type */
              parser->file_data->info.filetype = CURLFILETYPE_FILE;
            }

            parser->file_data->info.flags |= CURLFINFOFLAG_KNOWN_SIZE;
            parser->item_length = 0;
            parser->state.NT.main = PL_WINNT_FILENAME;
            parser->state.NT.sub.filename = PL_WINNT_FILENAME_PRESPACE;
          }
          break;
        }
        break;
      case PL_WINNT_FILENAME:
        switch(parser->state.NT.sub.filename) {
        case PL_WINNT_FILENAME_PRESPACE:
          if(c != ' ') {
            parser->item_offset = finfo->b_used -1;
            parser->item_length = 1;
            parser->state.NT.sub.filename = PL_WINNT_FILENAME_CONTENT;
          }
          break;
        case PL_WINNT_FILENAME_CONTENT:
          parser->item_length++;
          if(c == '\r') {
            parser->state.NT.sub.filename = PL_WINNT_FILENAME_WINEOL;
            finfo->b_data[finfo->b_used - 1] = 0;
          }
          else if(c == '\n') {
            parser->offsets.filename = parser->item_offset;
            finfo->b_data[finfo->b_used - 1] = 0;
            parser->offsets.filename = parser->item_offset;
            result = ftp_pl_insert_finfo(conn, infop);
            if(result) {
              parser->error = result;
              goto fail;
            }
            parser->state.NT.main = PL_WINNT_DATE;
            parser->state.NT.sub.filename = PL_WINNT_FILENAME_PRESPACE;
          }
          break;
        case PL_WINNT_FILENAME_WINEOL:
          if(c == '\n') {
            parser->offsets.filename = parser->item_offset;
            result = ftp_pl_insert_finfo(conn, infop);
            if(result) {
              parser->error = result;
              goto fail;
            }
            parser->state.NT.main = PL_WINNT_DATE;
            parser->state.NT.sub.filename = PL_WINNT_FILENAME_PRESPACE;
          }
          else {
            parser->error = CURLE_FTP_BAD_FILE_LIST;
            goto fail;
          }
          break;
        }
        break;
      }
      break;
    default:
      retsize = bufflen + 1;
      goto fail;
    }

    i++;
  }
  return retsize;

fail:

  /* Clean up any allocated memory. */
  if(parser->file_data) {
    Curl_fileinfo_cleanup(parser->file_data);
    parser->file_data = NULL;
  }

  return retsize;
}