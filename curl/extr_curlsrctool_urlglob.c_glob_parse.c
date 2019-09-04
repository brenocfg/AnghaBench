#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* glob_buffer; scalar_t__ size; } ;
typedef  TYPE_1__ URLGlob ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  GLOBERROR (char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ GLOB_PATTERN_NUM ; 
 int /*<<< orphan*/  glob_fixed (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  glob_range (TYPE_1__*,char**,size_t*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glob_set (TYPE_1__*,char**,size_t*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  peek_ipv6 (char*,size_t*) ; 

__attribute__((used)) static CURLcode glob_parse(URLGlob *glob, char *pattern,
                           size_t pos, unsigned long *amount)
{
  /* processes a literal string component of a URL
     special characters '{' and '[' branch to set/range processing functions
   */
  CURLcode res = CURLE_OK;
  int globindex = 0; /* count "actual" globs */

  *amount = 1;

  while(*pattern && !res) {
    char *buf = glob->glob_buffer;
    size_t sublen = 0;
    while(*pattern && *pattern != '{') {
      if(*pattern == '[') {
        /* skip over IPv6 literals and [] */
        size_t skip = 0;
        if(!peek_ipv6(pattern, &skip) && (pattern[1] == ']'))
          skip = 2;
        if(skip) {
          memcpy(buf, pattern, skip);
          buf += skip;
          pattern += skip;
          sublen += skip;
          continue;
        }
        break;
      }
      if(*pattern == '}' || *pattern == ']')
        return GLOBERROR("unmatched close brace/bracket", pos,
                         CURLE_URL_MALFORMAT);

      /* only allow \ to escape known "special letters" */
      if(*pattern == '\\' &&
         (*(pattern + 1) == '{' || *(pattern + 1) == '[' ||
          *(pattern + 1) == '}' || *(pattern + 1) == ']') ) {

        /* escape character, skip '\' */
        ++pattern;
        ++pos;
      }
      *buf++ = *pattern++; /* copy character to literal */
      ++pos;
      sublen++;
    }
    if(sublen) {
      /* we got a literal string, add it as a single-item list */
      *buf = '\0';
      res = glob_fixed(glob, glob->glob_buffer, sublen);
    }
    else {
      switch (*pattern) {
      case '\0': /* done  */
        break;

      case '{':
        /* process set pattern */
        pattern++;
        pos++;
        res = glob_set(glob, &pattern, &pos, amount, globindex++);
        break;

      case '[':
        /* process range pattern */
        pattern++;
        pos++;
        res = glob_range(glob, &pattern, &pos, amount, globindex++);
        break;
      }
    }

    if(++glob->size >= GLOB_PATTERN_NUM)
      return GLOBERROR("too many globs", pos, CURLE_URL_MALFORMAT);
  }
  return res;
}