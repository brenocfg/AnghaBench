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
typedef  int CURLUPart ;

/* Variables and functions */
 int CURLUPART_FRAGMENT ; 
 int CURLUPART_HOST ; 
 int CURLUPART_OPTIONS ; 
 int CURLUPART_PASSWORD ; 
 int CURLUPART_PATH ; 
 int CURLUPART_PORT ; 
 int CURLUPART_QUERY ; 
 int CURLUPART_SCHEME ; 
 int CURLUPART_URL ; 
 int CURLUPART_USER ; 
 int CURLUPART_ZONEID ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static CURLUPart part2id(char *part)
{
  if(!strcmp("url", part))
    return CURLUPART_URL;
  if(!strcmp("scheme", part))
    return CURLUPART_SCHEME;
  if(!strcmp("user", part))
    return CURLUPART_USER;
  if(!strcmp("password", part))
    return CURLUPART_PASSWORD;
  if(!strcmp("options", part))
    return CURLUPART_OPTIONS;
  if(!strcmp("host", part))
    return CURLUPART_HOST;
  if(!strcmp("port", part))
    return CURLUPART_PORT;
  if(!strcmp("path", part))
    return CURLUPART_PATH;
  if(!strcmp("query", part))
    return CURLUPART_QUERY;
  if(!strcmp("fragment", part))
    return CURLUPART_FRAGMENT;
  if(!strcmp("zoneid", part))
    return CURLUPART_ZONEID;
  return 9999; /* bad input => bad output */
}