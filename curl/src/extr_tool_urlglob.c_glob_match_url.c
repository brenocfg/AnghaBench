#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  numbuf ;
struct TYPE_10__ {int /*<<< orphan*/  ptr_n; int /*<<< orphan*/  padlength; } ;
struct TYPE_9__ {char ptr_c; } ;
struct TYPE_8__ {char** elements; size_t ptr_s; } ;
struct TYPE_11__ {TYPE_3__ NumRange; TYPE_2__ CharRange; TYPE_1__ Set; } ;
struct TYPE_12__ {int globindex; int type; TYPE_4__ content; } ;
typedef  TYPE_5__ URLPattern ;
struct TYPE_13__ {unsigned long size; TYPE_5__* pattern; } ;
typedef  TYPE_6__ URLGlob ;
typedef  scalar_t__ SANITIZEcode ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_FAILED_INIT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 scalar_t__ ISDIGIT (char) ; 
 int SANITIZE_ALLOW_PATH ; 
 int SANITIZE_ALLOW_RESERVED ; 
#define  UPTCharRange 130 
#define  UPTNumRange 129 
#define  UPTSet 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ sanitize_file_name (char**,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 unsigned long strtoul (char*,char**,int) ; 

CURLcode glob_match_url(char **result, char *filename, URLGlob *glob)
{
  char *target;
  size_t allocsize;
  char numbuf[18];
  char *appendthis = (char *)"";
  size_t appendlen = 0;
  size_t stringlen = 0;

  *result = NULL;

  /* We cannot use the glob_buffer for storage here since the filename may
   * be longer than the URL we use. We allocate a good start size, then
   * we need to realloc in case of need.
   */
  allocsize = strlen(filename) + 1; /* make it at least one byte to store the
                                       trailing zero */
  target = malloc(allocsize);
  if(!target)
    return CURLE_OUT_OF_MEMORY;

  while(*filename) {
    if(*filename == '#' && ISDIGIT(filename[1])) {
      char *ptr = filename;
      unsigned long num = strtoul(&filename[1], &filename, 10);
      URLPattern *pat = NULL;

      if(num < glob->size) {
        unsigned long i;
        num--; /* make it zero based */
        /* find the correct glob entry */
        for(i = 0; i<glob->size; i++) {
          if(glob->pattern[i].globindex == (int)num) {
            pat = &glob->pattern[i];
            break;
          }
        }
      }

      if(pat) {
        switch(pat->type) {
        case UPTSet:
          if(pat->content.Set.elements) {
            appendthis = pat->content.Set.elements[pat->content.Set.ptr_s];
            appendlen =
              strlen(pat->content.Set.elements[pat->content.Set.ptr_s]);
          }
          break;
        case UPTCharRange:
          numbuf[0] = pat->content.CharRange.ptr_c;
          numbuf[1] = 0;
          appendthis = numbuf;
          appendlen = 1;
          break;
        case UPTNumRange:
          msnprintf(numbuf, sizeof(numbuf), "%0*lu",
                    pat->content.NumRange.padlength,
                    pat->content.NumRange.ptr_n);
          appendthis = numbuf;
          appendlen = strlen(numbuf);
          break;
        default:
          fprintf(stderr, "internal error: invalid pattern type (%d)\n",
                  (int)pat->type);
          Curl_safefree(target);
          return CURLE_FAILED_INIT;
        }
      }
      else {
        /* #[num] out of range, use the #[num] in the output */
        filename = ptr;
        appendthis = filename++;
        appendlen = 1;
      }
    }
    else {
      appendthis = filename++;
      appendlen = 1;
    }
    if(appendlen + stringlen >= allocsize) {
      char *newstr;
      /* we append a single byte to allow for the trailing byte to be appended
         at the end of this function outside the while() loop */
      allocsize = (appendlen + stringlen) * 2;
      newstr = realloc(target, allocsize + 1);
      if(!newstr) {
        Curl_safefree(target);
        return CURLE_OUT_OF_MEMORY;
      }
      target = newstr;
    }
    memcpy(&target[stringlen], appendthis, appendlen);
    stringlen += appendlen;
  }
  target[stringlen]= '\0';

#if defined(MSDOS) || defined(WIN32)
  {
    char *sanitized;
    SANITIZEcode sc = sanitize_file_name(&sanitized, target,
                                         (SANITIZE_ALLOW_PATH |
                                          SANITIZE_ALLOW_RESERVED));
    Curl_safefree(target);
    if(sc)
      return CURLE_URL_MALFORMAT;
    target = sanitized;
  }
#endif /* MSDOS || WIN32 */

  *result = target;
  return CURLE_OK;
}