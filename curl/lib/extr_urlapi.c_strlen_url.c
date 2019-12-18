#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ find_host_sep (char const*) ; 
 int /*<<< orphan*/  urlchar_needs_escaping (unsigned char const) ; 

__attribute__((used)) static size_t strlen_url(const char *url, bool relative)
{
  const unsigned char *ptr;
  size_t newlen = 0;
  bool left = TRUE; /* left side of the ? */
  const unsigned char *host_sep = (const unsigned char *) url;

  if(!relative)
    host_sep = (const unsigned char *) find_host_sep(url);

  for(ptr = (unsigned char *)url; *ptr; ptr++) {

    if(ptr < host_sep) {
      ++newlen;
      continue;
    }

    switch(*ptr) {
    case '?':
      left = FALSE;
      /* FALLTHROUGH */
    default:
      if(urlchar_needs_escaping(*ptr))
        newlen += 2;
      newlen++;
      break;
    case ' ':
      if(left)
        newlen += 3;
      else
        newlen++;
      break;
    }
  }
  return newlen;
}