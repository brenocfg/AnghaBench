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
struct curl_slist {int dummy; } ;

/* Variables and functions */
 struct curl_slist* curl_slist_append (struct curl_slist*,char const*) ; 

__attribute__((used)) static int slist_append(struct curl_slist **plist, const char *data)
{
  struct curl_slist *s = curl_slist_append(*plist, data);

  if(!s)
    return -1;

  *plist = s;
  return 0;
}