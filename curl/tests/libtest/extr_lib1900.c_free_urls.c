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
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int blacklist_num_servers ; 
 int blacklist_num_sites ; 
 int num_handles ; 
 int /*<<< orphan*/ * server_blacklist ; 
 int /*<<< orphan*/ * site_blacklist ; 
 int /*<<< orphan*/ * urlstring ; 

__attribute__((used)) static void free_urls(void)
{
  int i;
  for(i = 0; i < num_handles; i++) {
    Curl_safefree(urlstring[i]);
  }
  for(i = 0; i < blacklist_num_servers; i++) {
    Curl_safefree(server_blacklist[i]);
  }
  for(i = 0; i < blacklist_num_sites; i++) {
    Curl_safefree(site_blacklist[i]);
  }
}