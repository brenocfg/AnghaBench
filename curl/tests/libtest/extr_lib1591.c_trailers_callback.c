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
 int CURL_TRAILERFUNC_OK ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,char*) ; 

__attribute__((used)) static int trailers_callback(struct curl_slist **list, void *userdata)
{
  (void)userdata;
  *list = curl_slist_append(*list, "my-super-awesome-trailer: trail1");
  *list = curl_slist_append(*list, "my-other-awesome-trailer: trail2");
  return CURL_TRAILERFUNC_OK;
}