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
struct curl_slist {char* data; } ;

/* Variables and functions */
 scalar_t__ strncasecompare (char*,char const*,size_t) ; 

__attribute__((used)) static char *match_header(struct curl_slist *hdr, const char *lbl, size_t len)
{
  char *value = NULL;

  if(strncasecompare(hdr->data, lbl, len) && hdr->data[len] == ':')
    for(value = hdr->data + len + 1; *value == ' '; value++)
      ;
  return value;
}