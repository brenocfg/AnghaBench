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
 int /*<<< orphan*/  ASCII_CCSID ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,char const*) ; 
 char* dynconvert (int /*<<< orphan*/ ,char const*,int,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 

struct curl_slist *
curl_slist_append_ccsid(struct curl_slist *list,
                        const char *data, unsigned int ccsid)

{
  char *s;

  s = (char *) NULL;

  if(!data)
    return curl_slist_append(list, data);

  s = dynconvert(ASCII_CCSID, data, -1, ccsid);

  if(!s)
    return (struct curl_slist *) NULL;

  list = curl_slist_append(list, s);
  free(s);
  return list;
}