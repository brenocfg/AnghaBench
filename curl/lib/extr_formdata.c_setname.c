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
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  curl_mime_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static CURLcode setname(curl_mimepart *part, const char *name, size_t len)
{
  char *zname;
  CURLcode res;

  if(!name || !len)
    return curl_mime_name(part, name);
  zname = malloc(len + 1);
  if(!zname)
    return CURLE_OUT_OF_MEMORY;
  memcpy(zname, name, len);
  zname[len] = '\0';
  res = curl_mime_name(part, zname);
  free(zname);
  return res;
}