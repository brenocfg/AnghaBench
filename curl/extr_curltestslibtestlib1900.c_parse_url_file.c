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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t blacklist_num_servers ; 
 size_t blacklist_num_sites ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fscanf (int /*<<< orphan*/ *,char*,...) ; 
 size_t num_handles ; 
 int /*<<< orphan*/ ** server_blacklist ; 
 int /*<<< orphan*/ ** site_blacklist ; 
 void* strdup (char*) ; 
 void** urlstring ; 
 int* urltime ; 

__attribute__((used)) static int parse_url_file(const char *filename)
{
  FILE *f;
  int filetime;
  char buf[200];

  num_handles = 0;
  blacklist_num_sites = 0;
  blacklist_num_servers = 0;

  f = fopen(filename, "rb");
  if(!f)
    return 0;

  while(!feof(f)) {
    if(fscanf(f, "%d %199s\n", &filetime, buf)) {
      urltime[num_handles] = filetime;
      urlstring[num_handles] = strdup(buf);
      num_handles++;
      continue;
    }

    if(fscanf(f, "blacklist_site %199s\n", buf)) {
      site_blacklist[blacklist_num_sites] = strdup(buf);
      blacklist_num_sites++;
      continue;
    }

    break;
  }
  fclose(f);

  site_blacklist[blacklist_num_sites] = NULL;
  server_blacklist[blacklist_num_servers] = NULL;
  return num_handles;
}