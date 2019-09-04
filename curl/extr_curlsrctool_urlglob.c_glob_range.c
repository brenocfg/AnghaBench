#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned long ptr_n; unsigned long min_n; unsigned long max_n; unsigned long step; scalar_t__ padlength; } ;
struct TYPE_7__ {int step; char ptr_c; char min_c; char max_c; } ;
struct TYPE_9__ {TYPE_2__ NumRange; TYPE_1__ CharRange; } ;
struct TYPE_10__ {int globindex; TYPE_3__ content; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ URLPattern ;
struct TYPE_11__ {size_t size; TYPE_4__* pattern; } ;
typedef  TYPE_5__ URLGlob ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  GLOBERROR (char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ ISALPHA (char) ; 
 scalar_t__ ISBLANK (char) ; 
 scalar_t__ ISDIGIT (char) ; 
 int /*<<< orphan*/  UPTCharRange ; 
 int /*<<< orphan*/  UPTNumRange ; 
 scalar_t__ errno ; 
 scalar_t__ multiply (unsigned long*,int) ; 
 int sscanf (char*,char*,char*,char*,char*) ; 
 unsigned long strtoul (char*,char**,int) ; 

__attribute__((used)) static CURLcode glob_range(URLGlob *glob, char **patternp,
                           size_t *posp, unsigned long *amount,
                           int globindex)
{
  /* processes a range expression with the point behind the opening '['
     - char range: e.g. "a-z]", "B-Q]"
     - num range: e.g. "0-9]", "17-2000]"
     - num range with leading zeros: e.g. "001-999]"
     expression is checked for well-formedness and collected until the next ']'
  */
  URLPattern *pat;
  int rc;
  char *pattern = *patternp;
  char *c;

  pat = &glob->pattern[glob->size];
  pat->globindex = globindex;

  if(ISALPHA(*pattern)) {
    /* character range detected */
    char min_c;
    char max_c;
    char end_c;
    unsigned long step = 1;

    pat->type = UPTCharRange;

    rc = sscanf(pattern, "%c-%c%c", &min_c, &max_c, &end_c);

    if(rc == 3) {
      if(end_c == ':') {
        char *endp;
        errno = 0;
        step = strtoul(&pattern[4], &endp, 10);
        if(errno || &pattern[4] == endp || *endp != ']')
          step = 0;
        else
          pattern = endp + 1;
      }
      else if(end_c != ']')
        /* then this is wrong */
        rc = 0;
      else
        /* end_c == ']' */
        pattern += 4;
    }

    *posp += (pattern - *patternp);

    if(rc != 3 || !step || step > (unsigned)INT_MAX ||
       (min_c == max_c && step != 1) ||
       (min_c != max_c && (min_c > max_c || step > (unsigned)(max_c - min_c) ||
                           (max_c - min_c) > ('z' - 'a'))))
      /* the pattern is not well-formed */
      return GLOBERROR("bad range", *posp, CURLE_URL_MALFORMAT);

    /* if there was a ":[num]" thing, use that as step or else use 1 */
    pat->content.CharRange.step = (int)step;
    pat->content.CharRange.ptr_c = pat->content.CharRange.min_c = min_c;
    pat->content.CharRange.max_c = max_c;

    if(multiply(amount, ((pat->content.CharRange.max_c -
                          pat->content.CharRange.min_c) /
                         pat->content.CharRange.step + 1)))
      return GLOBERROR("range overflow", *posp, CURLE_URL_MALFORMAT);
  }
  else if(ISDIGIT(*pattern)) {
    /* numeric range detected */
    unsigned long min_n;
    unsigned long max_n = 0;
    unsigned long step_n = 0;
    char *endp;

    pat->type = UPTNumRange;
    pat->content.NumRange.padlength = 0;

    if(*pattern == '0') {
      /* leading zero specified, count them! */
      c = pattern;
      while(ISDIGIT(*c)) {
        c++;
        ++pat->content.NumRange.padlength; /* padding length is set for all
                                              instances of this pattern */
      }
    }

    errno = 0;
    min_n = strtoul(pattern, &endp, 10);
    if(errno || (endp == pattern))
      endp = NULL;
    else {
      if(*endp != '-')
        endp = NULL;
      else {
        pattern = endp + 1;
        while(*pattern && ISBLANK(*pattern))
          pattern++;
        if(!ISDIGIT(*pattern)) {
          endp = NULL;
          goto fail;
        }
        errno = 0;
        max_n = strtoul(pattern, &endp, 10);
        if(errno)
          /* overflow */
          endp = NULL;
        else if(*endp == ':') {
          pattern = endp + 1;
          errno = 0;
          step_n = strtoul(pattern, &endp, 10);
          if(errno)
            /* over/underflow situation */
            endp = NULL;
        }
        else
          step_n = 1;
        if(endp && (*endp == ']')) {
          pattern = endp + 1;
        }
        else
          endp = NULL;
      }
    }

    fail:
    *posp += (pattern - *patternp);

    if(!endp || !step_n ||
       (min_n == max_n && step_n != 1) ||
       (min_n != max_n && (min_n > max_n || step_n > (max_n - min_n))))
      /* the pattern is not well-formed */
      return GLOBERROR("bad range", *posp, CURLE_URL_MALFORMAT);

    /* typecasting to ints are fine here since we make sure above that we
       are within 31 bits */
    pat->content.NumRange.ptr_n = pat->content.NumRange.min_n = min_n;
    pat->content.NumRange.max_n = max_n;
    pat->content.NumRange.step = step_n;

    if(multiply(amount, ((pat->content.NumRange.max_n -
                          pat->content.NumRange.min_n) /
                         pat->content.NumRange.step + 1)))
      return GLOBERROR("range overflow", *posp, CURLE_URL_MALFORMAT);
  }
  else
    return GLOBERROR("bad range specification", *posp, CURLE_URL_MALFORMAT);

  *patternp = pattern;
  return CURLE_OK;
}