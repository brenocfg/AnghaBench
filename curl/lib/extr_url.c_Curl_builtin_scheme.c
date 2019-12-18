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
struct Curl_handler {int /*<<< orphan*/  scheme; } ;

/* Variables and functions */
 struct Curl_handler** protocols ; 
 scalar_t__ strcasecompare (int /*<<< orphan*/ ,char const*) ; 

const struct Curl_handler *Curl_builtin_scheme(const char *scheme)
{
  const struct Curl_handler * const *pp;
  const struct Curl_handler *p;
  /* Scan protocol handler table and match against 'scheme'. The handler may
     be changed later when the protocol specific setup function is called. */
  for(pp = protocols; (p = *pp) != NULL; pp++)
    if(strcasecompare(p->scheme, scheme))
      /* Protocol found in table. Check if allowed */
      return p;
  return NULL; /* not found */
}