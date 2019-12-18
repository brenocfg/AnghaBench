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
 size_t cookie_hash_domain (char const*,size_t) ; 
 char* get_top_domain (char const* const,size_t*) ; 
 scalar_t__ isip (char const* const) ; 

__attribute__((used)) static size_t cookiehash(const char * const domain)
{
  const char *top;
  size_t len;

  if(!domain || isip(domain))
    return 0;

  top = get_top_domain(domain, &len);
  return cookie_hash_domain(top, len);
}